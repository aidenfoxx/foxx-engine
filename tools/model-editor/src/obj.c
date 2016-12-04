#include "obj.h"

static Obj *objNew();
static void objFree(Obj*);
static int objProcessVec3(char*, Vec3*);
static int objProcessVec2(char*, Vec2*);
static int objProcessFace(char*, Vec3*, Vec3*, Vec3*);

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
	if (obj)
	{
		free(obj->vertices);
		free(obj->uvs);
		free(obj->normals);
		free(obj->indices);
		free(obj);
	}
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
	int headerSize = 4 * sizeof(int);
	int verticesSize = obj->verticesLength * sizeof(Vec3);
	int uvsSize = obj->uvsLength * sizeof(Vec2);
	int normalsSize = obj->normalsLength * sizeof(Vec3);
	int indicesSize = obj->indicesLength * sizeof(Vec3);
	int totalSize = headerSize + verticesSize + uvsSize + normalsSize + indicesSize;

	*femData = calloc(1, totalSize);

	/**
	 * Assemble the binary file.
	 * 16 byte header:
	 * (vertices, uvs, normals, indices)
	 */
	memcpy(&(*femData)[0], &obj->verticesLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int)], &obj->uvsLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int) * 2], &obj->normalsLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int) * 3], &obj->indicesLength, sizeof(int));
	memcpy(&(*femData)[headerSize], obj->vertices, verticesSize);
	memcpy(&(*femData)[headerSize + verticesSize], obj->uvs, uvsSize);
	memcpy(&(*femData)[headerSize + verticesSize + uvsSize], obj->normals, normalsSize);
	memcpy(&(*femData)[headerSize + verticesSize + uvsSize + normalsSize], obj->indices, indicesSize);

	objFree(obj);

	return totalSize;
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
	if (((*obj)->vertices = malloc((*obj)->verticesLength * sizeof(Vec3))) != NULL &&	
		((*obj)->uvs = malloc((*obj)->uvsLength * sizeof(Vec2))) != NULL &&
		((*obj)->normals = malloc((*obj)->normalsLength * sizeof(Vec3))) != NULL &&
		((*obj)->indices = malloc(((*obj)->indicesLength * 3) * sizeof(Vec3))) != NULL)
	{
		int error = 0;

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
					if (!objProcessVec3(currentLine, &(*obj)->vertices[(*obj)->verticesLength]))
					{
						(*obj)->verticesLength++;
					}
					else
					{
						error = 1;
					}
				}
				else if (currentLine[1] == 't' && currentLine[2] == ' ')
				{
					if (!objProcessVec2(currentLine, &(*obj)->uvs[(*obj)->uvsLength]))
					{
						(*obj)->uvsLength++;
					}
					else
					{
						error = 1;
					}
				}
				else if (currentLine[1] == 'n' && currentLine[2] == ' ')
				{
					if (!objProcessVec3(currentLine, &(*obj)->normals[(*obj)->normalsLength]))
					{
						(*obj)->normalsLength++;
					}
					else
					{
						error = 1;
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
					error = 1;
				}
			}

			if (nextLine)
			{
				*nextLine = '\n'; 
			}

			currentLine = nextLine ? (nextLine + 1) : NULL;
		}

		if (error)
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}

	/**
	 * Index object.
	 */
	Obj *indexed = objNew();
	HashTable *hashTable = hashTableNew((*obj)->indicesLength * 4);
	
	if (indexed &&
		hashTable &&
		(indexed->vertices = malloc((*obj)->indicesLength * sizeof(Vec3))) != NULL &&
		(indexed->uvs = malloc((*obj)->indicesLength * sizeof(Vec2))) != NULL &&
		(indexed->normals = malloc((*obj)->indicesLength * sizeof(Vec3))) != NULL &&
		(indexed->indices = malloc(((*obj)->indicesLength / 3) * sizeof(Vec3))) != NULL)
	{
		int error = 0;
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

			hashKey = hashTableKey(hashKey, (int)(*obj)->indices[i].x);
			hashKey = hashTableKey(hashKey, (int)(*obj)->indices[i].y);
			hashKey = hashTableKey(hashKey, (int)(*obj)->indices[i].z);

			if ((duplicate = hashTableGet(hashTable, hashKey)) == -1)
			{
				if ((*obj)->indices[i].x > 0.0f)
				{
					indexed->vertices[indexCount] = (*obj)->vertices[(int)(*obj)->indices[i].x - 1];
					indexed->verticesLength++;
				}
				else if ((*obj)->indices[i].x < 0.0f)
				{
					indexed->vertices[indexCount] = (*obj)->vertices[(*obj)->verticesLength + (int)(*obj)->indices[i].x];
					indexed->verticesLength++;
				}
				else
				{
					error = 1;
				}

				if ((*obj)->indices[i].y > 0.0f)
				{
					indexed->uvs[indexCount] = (*obj)->uvs[(int)(*obj)->indices[i].y - 1];
					indexed->uvsLength++;
				}
				else if ((*obj)->indices[i].y < 0.0f)
				{
					indexed->uvs[indexCount] = (*obj)->uvs[(*obj)->uvsLength + (int)(*obj)->indices[i].y];
					indexed->uvsLength++;
				}

				if ((*obj)->indices[i].z > 0.0f)
				{
					indexed->normals[indexCount] = (*obj)->normals[(int)(*obj)->indices[i].z - 1];
					indexed->normalsLength++;
				}
				else if ((*obj)->indices[i].z < 0.0f)
				{
					indexed->normals[indexCount] = (*obj)->normals[(*obj)->normalsLength + (int)(*obj)->indices[i].z];
					indexed->normalsLength++;
				}

				indexArray[i] = indexCount;
				indexCount++;
			}
			else
			{
				indexArray[i] = duplicate;
			}
		}

		if (!error)
		{
			if (indexed->uvsLength != indexed->verticesLength)
			{
				indexed->uvsLength = 0;
			}
			
			if (indexed->normalsLength != indexed->verticesLength)
			{
				indexed->normalsLength = 0;
			}

			indexed->vertices = realloc(indexed->vertices, indexed->verticesLength * sizeof(Vec3));
			indexed->uvs = realloc(indexed->uvs, indexed->uvsLength * sizeof(Vec2));
			indexed->normals = realloc(indexed->normals, indexed->normalsLength * sizeof(Vec3));

			hashTableFree(hashTable);
			objFree(*obj);

			*obj = indexed;

			return 0;
		}
	}

	hashTableFree(hashTable);
	objFree(indexed);

	return -4;
}

int objProcessVec3(char *line, Vec3 *vector3)
{
	if (sscanf(line, "%*s%f %f %f", &vector3->x, &vector3->y, &vector3->z) == 3)
	{
		return 0;
	}

	return -1;
}

int objProcessVec2(char *line, Vec2 *vector2)
{
	if (sscanf(line, "%*s%f %f", &vector2->x, &vector2->y) == 2)
	{
		return 0;
	}

	return -1;
}

int objProcessFace(char *line, Vec3 *face1, Vec3 *face2, Vec3 *face3)
{
	if (sscanf(line, "%*s%f/%f/%f %f/%f/%f %f/%f/%f", &face1->x, &face1->y, &face1->z, &face2->x, &face2->y, &face2->z, &face3->x, &face3->y, &face3->z) == 9)
	{
		return 0;
	}
	else if (sscanf(line, "%*s%f//%f %f//%f %f//%f", &face1->x, &face1->z, &face2->x, &face2->z, &face3->x, &face3->z) == 6)
	{
		face1->y = 0;
		face2->y = 0;
		face3->y = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%f/%f %f/%f %f/%f", &face1->x, &face1->y, &face2->x, &face2->y, &face3->x, &face3->y) == 6)
	{
		face1->z = 0;
		face2->z = 0;
		face3->z = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%f %f %f", &face1->x, &face2->x, &face3->x) == 3)
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