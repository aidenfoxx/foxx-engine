#include "obj.h"

static int objProcessVector3f(char*, Vector3f*);
static int objProcessVector2f(char*, Vector2f*);
static int objProcessFace(char*, Vector3i*, Vector3i*, Vector3i*);

void objInit(Obj *obj)
{
	obj->vertices = NULL;
	obj->uvs = NULL;
	obj->normals = NULL;
	obj->indices = NULL;
}

void objDestroy(Obj *obj)
{
	free(obj->vertices);
	free(obj->uvs);
	free(obj->normals);
	free(obj->indices);
}

int objToFem(uint8_t *objData, uint8_t **femData)
{
	Obj obj;
	objInit(&obj);

	if (objProcess(&obj, objData))
	{
		return -1;
	}

	/**
	 * The total length of all the OBJ
	 * elements and 4 integers for the
	 * header.
	 */
	int headerLength = 4 * sizeof(int);
	int verticesLength = obj.verticesLength * sizeof(Vector3f);
	int uvsLength = obj.uvsLength * sizeof(Vector2f);
	int normalsLength = obj.normalsLength * sizeof(Vector3f);
	int indicesLength = obj.indicesLength * sizeof(Vector3i);
	int totalLength = headerLength + verticesLength + uvsLength + normalsLength + indicesLength;

	*femData = malloc(totalLength * sizeof(uint8_t));

	/**
	 * Assemble the binary file.
	 * 16 byte header:
	 * (vertices, uvs, normals, indices)
	 */
	memcpy(&(*femData)[0], &obj.verticesLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int)], &obj.uvsLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int) * 2], &obj.normalsLength, sizeof(int));
	memcpy(&(*femData)[sizeof(int) * 3], &obj.indicesLength, sizeof(int));
	memcpy(&(*femData)[headerLength], obj.vertices, verticesLength);
	memcpy(&(*femData)[headerLength + verticesLength], obj.uvs, uvsLength);
	memcpy(&(*femData)[headerLength + verticesLength + uvsLength], obj.normals, normalsLength);
	memcpy(&(*femData)[headerLength + verticesLength + uvsLength + normalsLength], obj.indices, indicesLength);

	return totalLength;
}

int objProcess(Obj *obj, uint8_t *objData)
{
	char *currentLine;
	int returnError = 0;

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
				obj->verticesLength++;
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				obj->uvsLength++;
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				obj->normalsLength++;
			}
		}
		else if (currentLine[0] == 'f' && currentLine[1] == ' ')
		{
			obj->indicesLength += 3;
		}

		currentLine = nextLine ? (nextLine + 1) : NULL;
	}

	/**
	 * Extract object data.
	 */
	obj->vertices = malloc(obj->verticesLength * sizeof(Vector3f));
	obj->uvs = malloc(obj->uvsLength * sizeof(Vector2f));
	obj->normals = malloc(obj->normalsLength * sizeof(Vector3f));
	obj->indices = malloc((obj->indicesLength * 3) * sizeof(Vector3i));

	obj->verticesLength = 0;
	obj->uvsLength = 0;
	obj->normalsLength = 0;
	obj->indicesLength = 0;

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
				if (!objProcessVector3f(currentLine, &obj->vertices[obj->verticesLength]))
				{
					obj->verticesLength++;
				}
				else
				{
					returnError = -1;
				}
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				if (!objProcessVector2f(currentLine, &obj->uvs[obj->uvsLength]))
				{
					obj->uvsLength++;
				}
				else
				{
					returnError = -2;
				}
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				if (!objProcessVector3f(currentLine, &obj->normals[obj->normalsLength]))
				{
					obj->normalsLength++;
				}
				else
				{
					returnError = -3;
				}
			}
		}
		else if (currentLine[0] == 'f' && currentLine[1] == ' ')
		{
			if (!objProcessFace(currentLine, &obj->indices[obj->indicesLength], &obj->indices[obj->indicesLength + 1], &obj->indices[obj->indicesLength + 2]))
			{
				obj->indicesLength += 3;
			}
			else
			{
				returnError = -4;
			}
		}

		if (nextLine)
		{
			*nextLine = '\n'; 
		}

		currentLine = nextLine ? (nextLine + 1) : NULL;
	}

	/**
	 * Index object.
	 */
	if (!returnError)
	{
		Obj *indexed = malloc(sizeof(Obj));
		objInit(indexed);

		HashTable hashTable;
		hashTableInit(&hashTable, obj->indicesLength * 4);

		indexed->verticesLength = 0;
		indexed->uvsLength = 0;
		indexed->normalsLength = 0;
	
		indexed->vertices = malloc(obj->indicesLength * sizeof(Vector3f));
		indexed->uvs = malloc(obj->indicesLength * sizeof(Vector2f));
		indexed->normals = malloc(obj->indicesLength * sizeof(Vector3f));

		/**
		 * We already know the number of
		 * indices we will need.
		 */
		indexed->indicesLength = (obj->indicesLength / 3);
		indexed->indices = malloc(indexed->indicesLength * sizeof(Vector3i));

		int *indexArray = (int*)indexed->indices;
		int indexCount = 0;

		for (int i = 0; i < obj->indicesLength; i++)
		{
			int duplicate;
			int hashKey = 0;

			hashKey = hashTableKey(obj->indices[i].x, hashKey);
			hashKey = hashTableKey(obj->indices[i].y, hashKey);
			hashKey = hashTableKey(obj->indices[i].z, hashKey);

			if ((duplicate = hashTableGet(&hashTable, hashKey)) < 0)
			{
				if (obj->indices[i].x > 0)
				{
					indexed->vertices[indexCount] = obj->vertices[obj->indices[i].x - 1];
					indexed->verticesLength++;
				}
				else if (obj->indices[i].x < 0)
				{
					indexed->vertices[indexCount] = obj->vertices[obj->verticesLength + obj->indices[i].x];
					indexed->verticesLength++;
				}
				else
				{
					returnError = -5;
				}

				if (obj->indices[i].y > 0)
				{
					indexed->uvs[indexCount] = obj->uvs[obj->indices[i].y - 1];
					indexed->uvsLength++;
				}
				else if (obj->indices[i].y < 0)
				{
					indexed->uvs[indexCount] = obj->uvs[obj->uvsLength + obj->indices[i].y];
					indexed->uvsLength++;
				}

				if (obj->indices[i].z > 0)
				{
					indexed->normals[indexCount] = obj->normals[obj->indices[i].z - 1];
					indexed->normalsLength++;
				}
				else if (obj->indices[i].z < 0)
				{
					indexed->normals[indexCount] = obj->normals[obj->normalsLength + obj->indices[i].z];
					indexed->normalsLength++;
				}

				hashTableSet(&hashTable, hashKey, indexCount);

				indexArray[i] = indexCount;
				indexCount++;
			}
			else
			{
				indexArray[i] = duplicate;
			}
		}

		hashTableDestroy(&hashTable);

		if (!returnError)
		{
			if (indexed->uvsLength != indexed->verticesLength)
			{
				indexed->uvsLength = 0;
			}
			
			if (indexed->normalsLength != indexed->verticesLength)
			{
				indexed->normalsLength = 0;
			}

			objDestroy(obj);

			indexed->vertices = realloc(indexed->vertices, indexed->verticesLength * sizeof(Vector3f));
			indexed->uvs = realloc(indexed->uvs, indexed->uvsLength * sizeof(Vector2f));
			indexed->normals = realloc(indexed->normals, indexed->normalsLength * sizeof(Vector3f));

			*obj = *indexed;
		}
		else
		{
			free(indexed);
		}
	}

	return returnError;
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

int objProcessFace(char *line, Vector3i *index1, Vector3i *index2, Vector3i *index3)
{
	if (sscanf(line, "%*s%i/%i/%i %i/%i/%i %i/%i/%i", &index1->x, &index1->y, &index1->z, &index2->x, &index2->y, &index2->z, &index3->x, &index3->y, &index3->z) == 9)
	{
		return 0;
	}
	else if (sscanf(line, "%*s%i//%i %i//%i %i//%i", &index1->x, &index1->z, &index2->x, &index2->z, &index3->x, &index3->z) == 6)
	{
		index1->y = 0;
		index2->y = 0;
		index3->y = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i/%i %i/%i %i/%i", &index1->x, &index1->y, &index2->x, &index2->y, &index3->x, &index3->y) == 6)
	{
		index1->z = 0;
		index2->z = 0;
		index3->z = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i %i %i", &index1->x, &index2->x, &index3->x) == 3)
	{
		index1->y = 0;
		index2->y = 0;
		index3->y = 0;

		index1->z = 0;
		index2->z = 0;
		index3->z = 0;

		return 0;
	}

	return -1;
}