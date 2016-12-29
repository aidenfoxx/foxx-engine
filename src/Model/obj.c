#include "Model/obj.h"

static int modelObjProcessVec3(char*, Vec3*);
static int modelObjProcessVec2(char*, Vec2*);
static int modelObjProcessFace(char*, int*);
static int modelObjRead(const char*, uint8_t**);

Model *modelObjNew(uint8_t *data)
{
	Model *model;

	Vec3 *vertices = NULL;
	Vec2 *uvs = NULL;
	Vec3 *normals = NULL;
	int *indices = NULL;

	int error = 0;
	int verticesLength = 0;
	int uvsLength = 0;
	int normalsLength = 0;
	int indicesLength = 0;

	/**
	 * Get object info.
	 */
	char *currentLine = (char*)data;

	while (currentLine)
	{
		char *nextLine = strchr(currentLine, '\n');

		if (currentLine[0] == 'v')
		{
			if (currentLine[1] == ' ')
			{
				verticesLength++;
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				uvsLength++;
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				normalsLength++;
			}
		}
		else if (currentLine[0] == 'f' && currentLine[1] == ' ')
		{
			indicesLength += 3;
		}

		currentLine = nextLine ? (nextLine + 1) : NULL;
	}

	/**
	 * Extract object data.
	 */
	if ((vertices = malloc(verticesLength * sizeof(Vec3))) != NULL &&	
		(uvs = malloc(uvsLength * sizeof(Vec2))) != NULL &&
		(normals = malloc(normalsLength * sizeof(Vec3))) != NULL &&
		(indices = malloc((indicesLength * 9) * sizeof(int))) != NULL)
	{
		verticesLength = 0;
		uvsLength = 0;
		normalsLength = 0;
		indicesLength = 0;

		currentLine = (char*)data;

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
					if (!modelObjProcessVec3(currentLine, &vertices[verticesLength]))
					{
						verticesLength++;
					}
					else
					{
						error = -1;
					}
				}
				else if (currentLine[1] == 't' && currentLine[2] == ' ')
				{
					if (!modelObjProcessVec2(currentLine, &uvs[uvsLength]))
					{
						uvsLength++;
					}
					else
					{
						error = -1;
					}
				}
				else if (currentLine[1] == 'n' && currentLine[2] == ' ')
				{
					if (!modelObjProcessVec3(currentLine, &normals[normalsLength]))
					{
						normalsLength++;
					}
					else
					{
						error = -1;
					}
				}
			}
			else if (currentLine[0] == 'f' && currentLine[1] == ' ')
			{
				if (!modelObjProcessFace(currentLine, &indices[indicesLength * 3]))
				{
					indicesLength += 3;
				}
				else
				{
					error = -1;
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
		if (!error)
		{
			Vec3 *indexedVertices = NULL;
			Vec2 *indexedUVs = NULL;
			Vec3 *indexedNormals = NULL;
			int *indexedIndices = NULL;

			int indexedVerticesLength = 0;
			int indexedUVsLength = 0;
			int indexedNormalsLength = 0;
			int indexedIndicesLength = indicesLength;
			
			HashTable *hashTable = NULL;

			if ((hashTable = hashTableNew(indicesLength * 4)) &&
				(indexedVertices = malloc(indicesLength * sizeof(Vec3))) != NULL &&
				(indexedUVs = malloc(indicesLength * sizeof(Vec2))) != NULL &&
				(indexedNormals = malloc(indicesLength * sizeof(Vec3))) != NULL &&
				(indexedIndices = malloc(indicesLength * sizeof(int))) != NULL)
			{
				int indexCount = 0;

				for (int i = 0; i < indicesLength; i++)
				{
					int x = i * 3;
					int hashKey = 0;
					
					int duplicate;

					hashKey = hashTableKey(hashKey, (int)indices[x]);
					hashKey = hashTableKey(hashKey, (int)indices[x + 1]);
					hashKey = hashTableKey(hashKey, (int)indices[x + 2]);

					if ((duplicate = hashTableGet(hashTable, hashKey)) == -1)
					{
						if (indices[x] > 0.0f)
						{
							indexedVertices[indexCount] = vertices[indices[x] - 1];
							indexedVerticesLength++;
						}
						else if (indices[x] < 0.0f)
						{
							indexedVertices[indexCount] = vertices[verticesLength + indices[x]];
							indexedVerticesLength++;
						}
						else
						{
							error = -2;
						}

						if (indices[x + 1] > 0.0f)
						{
							indexedUVs[indexCount] = uvs[indices[x + 1] - 1];
							indexedUVsLength++;
						}
						else if (indices[x + 1] < 0.0f)
						{
							indexedUVs[indexCount] = uvs[uvsLength + indices[x + 1]];
							indexedUVsLength++;
						}

						if (indices[x + 2] > 0.0f)
						{
							indexedNormals[indexCount] = normals[indices[x + 2] - 1];
							indexedNormalsLength++;
						}
						else if (indices[x + 2] < 0.0f)
						{
							indexedNormals[indexCount] = normals[normalsLength + indices[x + 2]];
							indexedNormalsLength++;
						}

						hashTableSet(hashTable, hashKey, indexCount);

						indexedIndices[i] = indexCount;
						indexCount++;
					}
					else
					{
						indexedIndices[i] = duplicate;
					}
				}

				if (!error)
				{
					if (indexedUVsLength != indexedVerticesLength)
					{
						indexedUVsLength = 0;
					}
					
					if (indexedNormalsLength != indexedVerticesLength)
					{
						indexedNormalsLength = 0;
					}

					indexedVertices = realloc(indexedVertices, indexedVerticesLength * sizeof(Vec3));
					indexedUVs = realloc(indexedUVs, indexedUVsLength * sizeof(Vec2));
					indexedNormals = realloc(indexedNormals, indexedNormalsLength * sizeof(Vec3));

					model = modelNew(indexedVertices, indexedUVs, indexedNormals, indexedIndices, indexedVerticesLength, indexedUVsLength, indexedNormalsLength, indexedIndicesLength);
				}
			}

			hashTableFree(hashTable);

			free(indexedVertices);
			free(indexedUVs);
			free(indexedNormals);
			free(indexedIndices);
		}
	}

	free(vertices);
	free(uvs);
	free(normals);
	free(indices);

	return model;
}

Model *modelObjLoad(const char *path)
{
	Model *model = NULL;
	uint8_t *modelData = NULL;

	if (modelObjRead(path, &modelData) > 0)
	{
		model = modelObjNew(modelData);
	}

	free(modelData);

	return model;
}

int modelObjProcessVec3(char *line, Vec3 *vec3)
{
	if (sscanf(line, "%*s%f %f %f", &vec3->x, &vec3->y, &vec3->z) == 3)
	{
		return 0;
	}

	return -1;
}

int modelObjProcessVec2(char *line, Vec2 *vec2)
{
	if (sscanf(line, "%*s%f %f", &vec2->x, &vec2->y) == 2)
	{
		return 0;
	}

	return -1;
}

int modelObjProcessFace(char *line, int *face)
{
	if (sscanf(line, "%*s%i/%i/%i %i/%i/%i %i/%i/%i", &face[0], &face[1], &face[2], &face[3], &face[4], &face[5], &face[6], &face[7], &face[8]) == 9)
	{
		return 0;
	}
	else if (sscanf(line, "%*s%i//%i %i//%i %i//%i", &face[0], &face[2], &face[3], &face[5], &face[6], &face[8]) == 6)
	{
		face[1] = 0;
		face[4] = 0;
		face[7] = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i/%i %i/%i %i/%i", &face[0], &face[1], &face[3], &face[4], &face[6], &face[7]) == 6)
	{
		face[2] = 0;
		face[5] = 0;
		face[8] = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i %i %i", &face[0], &face[3], &face[6]) == 3)
	{
		face[1] = 0;
		face[4] = 0;
		face[7] = 0;

		face[2] = 0;
		face[5] = 0;
		face[8] = 0;

		return 0;
	}

	return -1;
}

int modelObjRead(const char *modelPath, uint8_t **modelData)
{
	FILE *model = fopen(modelPath, "rb");

	if (!model)
	{
		return 0;
	}

	fseek(model, 0, SEEK_END);
	long length = ftell(model);
	fseek(model, 0, SEEK_SET);

	*modelData = calloc(length + 1, 1);

	if (length != fread(*modelData, 1, length, model)) 
	{ 
		free(*modelData);
		return 0;
	}

	fclose(model);

	return length;
}