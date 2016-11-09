#include "obj.h"

static Obj *objNew();
static void objFree(Obj*);
static int objProcessVector3f(char*, Vector3f*);
static int objProcessVector2f(char*, Vector2f*);
static int objProcessFace(char*, Vector3i*, Vector3i*, Vector3i*);

Obj *objNew()
{
	Obj *obj;

	if ((obj = malloc(sizeof(Obj))) != NULL)
	{
		obj->verticesLength = 0;
		obj->uvsLength = 0;
		obj->normalsLength = 0;
		obj->indicesLength = 0;

		obj->vertices = NULL;
		obj->uvs = NULL;
		obj->normals = NULL;
		obj->indices = NULL;
	}

	return obj;
}

void objFree(Obj *obj)
{
	free(obj->vertices);
	free(obj->uvs);
	free(obj->normals);
	free(obj->indices);
	free(obj);
}

int objToFem(uint8_t *objData, uint8_t **femData)
{
	Obj *obj;

	if ((obj = objNew()) == NULL)
	{
		return -1;
	}

	if (objProcess(objData, &obj))
	{
		return -2;
	}

	/**
	 * The total length of all the OBJ
	 * elements and 4 integers for the
	 * header.
	 */
	int headerLength = 4 * sizeof(int);
	int verticesLength = obj->verticesLength * sizeof(Vector3f);
	int uvsLength = obj->uvsLength * sizeof(Vector2f);
	int normalsLength = obj->normalsLength * sizeof(Vector3f);
	int indicesLength = obj->indicesLength * sizeof(Vector3i);
	int totalLength = headerLength + verticesLength + uvsLength + normalsLength + indicesLength;

	*femData = malloc(totalLength * sizeof(uint8_t));

	/**
	 * Assemble the binary file.
	 * 16 byte header:
	 * (vertices, uvs, normals, indices)
	 */
	memcpy(&(*femData)[0], &obj->verticesLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int)], &obj->uvsLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int) * 2], &obj->normalsLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int) * 3], &obj->indicesLength, sizeof(int));
	memcpy(&(*femData)[headerLength], obj->vertices, verticesLength);
	memcpy(&(*femData)[headerLength + verticesLength], obj->uvs, uvsLength);
	memcpy(&(*femData)[headerLength + verticesLength + uvsLength], obj->normals, normalsLength);
	memcpy(&(*femData)[headerLength + verticesLength + uvsLength + normalsLength], obj->indices, indicesLength);

	objFree(obj);

	return totalLength;
}

int objProcess(uint8_t *objData, Obj **obj)
{
	char *currentLine;
	
	/**
	 * Get object info.
	 */
	currentLine = (char*)objData;

	while (currentLine)
	{
		char *nextLine = strchr(currentLine, '\n');

		if (currentLine[0] == 'v')
		{
			if (currentLine[1] == ' ')
			{
				(*obj)->verticesLength++;
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				(*obj)->uvsLength++;
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				(*obj)->normalsLength++;
			}
		}
		else if (currentLine[0] == 'f' && currentLine[1] == ' ')
		{
			(*obj)->indicesLength += 3;
		}

		currentLine = nextLine ? (nextLine + 1) : NULL;
	}

	/**
	 * Extract object data.
	 */
	if (((*obj)->vertices = malloc((*obj)->verticesLength * sizeof(Vector3f))) != NULL &&	
		((*obj)->uvs = malloc((*obj)->uvsLength * sizeof(Vector2f))) != NULL &&
		((*obj)->normals = malloc((*obj)->normalsLength * sizeof(Vector3f))) != NULL &&
		((*obj)->indices = malloc(((*obj)->indicesLength * 3) * sizeof(Vector3i))) != NULL)
	{
		int returnError = 0;

		(*obj)->verticesLength = 0;
		(*obj)->uvsLength = 0;
		(*obj)->normalsLength = 0;
		(*obj)->indicesLength = 0;

		currentLine = (char*)objData;

		while (currentLine)
		{
			char *nextLine = strchr(currentLine, '\n');

			if (nextLine)
			{
				*nextLine = '\0';
			}

			if (currentLine[0] == 'v')
			{
				if (currentLine[1] == ' ')
				{
					if (!objProcessVector3f(currentLine, &(*obj)->vertices[(*obj)->verticesLength]))
					{
						(*obj)->verticesLength++;
					}
					else
					{
						returnError = -1;
					}
				}
				else if (currentLine[1] == 't' && currentLine[2] == ' ')
				{
					if (!objProcessVector2f(currentLine, &(*obj)->uvs[(*obj)->uvsLength]))
					{
						(*obj)->uvsLength++;
					}
					else
					{
						returnError = -1;
					}
				}
				else if (currentLine[1] == 'n' && currentLine[2] == ' ')
				{
					if (!objProcessVector3f(currentLine, &(*obj)->normals[(*obj)->normalsLength]))
					{
						(*obj)->normalsLength++;
					}
					else
					{
						returnError = -1;
					}
				}
			}
			else if (currentLine[0] == 'f' && currentLine[1] == ' ')
			{
				if (!objProcessFace(currentLine, &(*obj)->indices[(*obj)->indicesLength], &(*obj)->indices[(*obj)->indicesLength + 1], &(*obj)->indices[(*obj)->indicesLength + 2]))
				{
					(*obj)->indicesLength += 3;
				}
				else
				{
					returnError = -1;
				}
			}

			if (nextLine)
			{
				*nextLine = '\n'; 
			}

			currentLine = nextLine ? (nextLine + 1) : NULL;
		}

		if (returnError)
		{
			return returnError;
		}
	}
	else
	{
		return -2;
	}

	/**
	 * Index object.
	 */
	Obj *indexed;
	HashTable *hashTable;

	if ((indexed = objNew()) != NULL &&
		(indexed->vertices = malloc((*obj)->indicesLength * sizeof(Vector3f))) != NULL &&
		(indexed->uvs = malloc((*obj)->indicesLength * sizeof(Vector2f))) != NULL &&
		(indexed->normals = malloc((*obj)->indicesLength * sizeof(Vector3f))) != NULL &&
		(indexed->indices = malloc(((*obj)->indicesLength / 3) * sizeof(Vector3i))) != NULL &&
		(hashTable = hashTableNew((*obj)->indicesLength * 4)) != NULL)
	{
		int returnError = 0;
		int indexCount = 0;
		int *indexArray = (int*)indexed->indices;

		/**
		 * We already know the number of
		 * indices we will need.
		 */
		indexed->indicesLength = ((*obj)->indicesLength / 3);

		for (int i = 0; i < (*obj)->indicesLength; i++)
		{
			int duplicate;
			int hashKey = 0;

			hashKey = hashTableKey((*obj)->indices[i].x, hashKey);
			hashKey = hashTableKey((*obj)->indices[i].y, hashKey);
			hashKey = hashTableKey((*obj)->indices[i].z, hashKey);

			if ((duplicate = hashTableGet(hashTable, hashKey)) < 0)
			{
				if ((*obj)->indices[i].x > 0)
				{
					indexed->vertices[indexCount] = (*obj)->vertices[(*obj)->indices[i].x - 1];
					indexed->verticesLength++;
				}
				else if ((*obj)->indices[i].x < 0)
				{
					indexed->vertices[indexCount] = (*obj)->vertices[(*obj)->verticesLength + (*obj)->indices[i].x];
					indexed->verticesLength++;
				}
				else
				{
					returnError = -3;
				}

				if ((*obj)->indices[i].y > 0)
				{
					indexed->uvs[indexCount] = (*obj)->uvs[(*obj)->indices[i].y - 1];
					indexed->uvsLength++;
				}
				else if ((*obj)->indices[i].y < 0)
				{
					indexed->uvs[indexCount] = (*obj)->uvs[(*obj)->uvsLength + (*obj)->indices[i].y];
					indexed->uvsLength++;
				}

				if ((*obj)->indices[i].z > 0)
				{
					indexed->normals[indexCount] = (*obj)->normals[(*obj)->indices[i].z - 1];
					indexed->normalsLength++;
				}
				else if ((*obj)->indices[i].z < 0)
				{
					indexed->normals[indexCount] = (*obj)->normals[(*obj)->normalsLength + (*obj)->indices[i].z];
					indexed->normalsLength++;
				}

				hashTableSet(hashTable, hashKey, indexCount);

				indexArray[i] = indexCount;
				indexCount++;
			}
			else
			{
				indexArray[i] = duplicate;
			}
		}

		hashTableFree(hashTable);

		if (returnError)
		{
			objFree(indexed);
			return returnError;
		}

		if (indexed->uvsLength != indexed->verticesLength)
		{
			indexed->uvsLength = 0;
		}
		
		if (indexed->normalsLength != indexed->verticesLength)
		{
			indexed->normalsLength = 0;
		}

		indexed->vertices = realloc(indexed->vertices, indexed->verticesLength * sizeof(Vector3f));
		indexed->uvs = realloc(indexed->uvs, indexed->uvsLength * sizeof(Vector2f));
		indexed->normals = realloc(indexed->normals, indexed->normalsLength * sizeof(Vector3f));

		objFree(*obj);

		*obj = indexed;
	}
	else
	{
		return -2;
	}

	return 0;
}

int objProcessVector3f(char *line, Vector3f *vector3)
{
	if (sscanf(line, "%*s%f %f %f", &vector3->x, &vector3->y, &vector3->z) == 3)
	{
		return 0;
	}

	return -1;
}

int objProcessVector2f(char *line, Vector2f *vector2)
{
	if (sscanf(line, "%*s%f %f", &vector2->x, &vector2->y) == 2)
	{
		return 0;
	}

	return -1;
}

int objProcessFace(char *line, Vector3i *face1, Vector3i *face2, Vector3i *face3)
{
	if (sscanf(line, "%*s%i/%i/%i %i/%i/%i %i/%i/%i", &face1->x, &face1->y, &face1->z, &face2->x, &face2->y, &face2->z, &face3->x, &face3->y, &face3->z) == 9)
	{
		return 0;
	}
	else if (sscanf(line, "%*s%i//%i %i//%i %i//%i", &face1->x, &face1->z, &face2->x, &face2->z, &face3->x, &face3->z) == 6)
	{
		face1->y = 0;
		face2->y = 0;
		face3->y = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i/%i %i/%i %i/%i", &face1->x, &face1->y, &face2->x, &face2->y, &face3->x, &face3->y) == 6)
	{
		face1->z = 0;
		face2->z = 0;
		face3->z = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i %i %i", &face1->x, &face2->x, &face3->x) == 3)
	{
		face1->y = 0;
		face2->y = 0;
		face3->y = 0;

		face1->z = 0;
		face2->z = 0;
		face3->z = 0;

		return 0;
	}

	return -1;
}