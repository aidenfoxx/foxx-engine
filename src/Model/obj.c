#include "Model/obj.h"

static int modelObjProcessVec3(char*, Vec3*);
static int modelObjProcessVec2(char*, Vec2*);
static int modelObjProcessFace(char*, Vec3*, Vec3*, Vec3*);
static int modelObjRead(const char*, uint8_t**);

Model *modelObjNew(uint8_t *data)
{
	Vec3 *vertices = NULL;
	Vec2 *uvs = NULL;
	Vec3 *normals = NULL;
	Vec3 *indices = NULL;

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
		(indices = malloc((indicesLength * 3) * sizeof(Vec3))) != NULL)
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
				if (!modelObjProcessFace(currentLine, &indices[indicesLength], &indices[indicesLength + 1], &indices[indicesLength + 2]))
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
			Vec3 *indexedIndices = NULL;

			int indexedVerticesLength = 0;
			int indexedUVsLength = 0;
			int indexedNormalsLength = 0;
			int indexedIndicesLength = 0;
			
			HashTable *hashTable = NULL;

			if ((hashTable = hashTableNew(indicesLength * 4)) &&
				(indexedVertices = malloc(indicesLength * sizeof(Vec3))) != NULL &&
				(indexedUVs = malloc(indicesLength * sizeof(Vec2))) != NULL &&
				(indexedNormals = malloc(indicesLength * sizeof(Vec3))) != NULL &&
				(indexedIndices = malloc((indicesLength / 3) * sizeof(Vec3))) != NULL)
			{
				int indexCount = 0;
				int *indexArray = (int*)indexedIndices;

				for (int i = 0; i < indicesLength; i++)
				{
					int duplicate;
					int hashKey = 0;

					hashKey = hashTableKey(hashKey, (int)indices[i].x);
					hashKey = hashTableKey(hashKey, (int)indices[i].y);
					hashKey = hashTableKey(hashKey, (int)indices[i].z);

					if ((duplicate = hashTableGet(hashTable, hashKey)) == -1)
					{
						if (indices[i].x > 0.0f)
						{
							indexedVertices[indexCount] = vertices[(int)indices[i].x - 1];
							indexedVerticesLength++;
						}
						else if (indices[i].x < 0.0f)
						{
							indexedVertices[indexCount] = vertices[verticesLength + (int)indices[i].x];
							indexedVerticesLength++;
						}
						else
						{
							error = -2;
						}

						if (indices[i].y > 0.0f)
						{
							indexedUVs[indexCount] = uvs[(int)indices[i].y - 1];
							indexedUVsLength++;
						}
						else if (indices[i].y < 0.0f)
						{
							indexedUVs[indexCount] = uvs[uvsLength + (int)indices[i].y];
							indexedUVsLength++;
						}

						if (indices[i].z > 0.0f)
						{
							indexedNormals[indexCount] = normals[(int)indices[i].z - 1];
							indexedNormalsLength++;
						}
						else if (indices[i].z < 0.0f)
						{
							indexedNormals[indexCount] = normals[normalsLength + (int)indices[i].z];
							indexedNormalsLength++;
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
					free(vertices);
					free(uvs);
					free(normals);
					free(indices);
					
					vertices = indexedVertices;
					uvs = indexedUVs;
					normals = indexedNormals;
					indices = indexedIndices;

					indexedVertices = NULL;
					indexedUVs = NULL;
					indexedNormals = NULL;
					indexedIndices = NULL;

					verticesLength = indexedVerticesLength;
					uvsLength = indexedUVsLength;
					normalsLength = indexedNormalsLength;
					indicesLength = indexedIndicesLength;

					if (uvsLength != verticesLength)
					{
						uvsLength = 0;
					}
					
					if (normalsLength != verticesLength)
					{
						normalsLength = 0;
					}

					vertices = realloc(vertices, verticesLength * sizeof(Vec3));
					uvs = realloc(uvs, uvsLength * sizeof(Vec2));
					normals = realloc(normals, normalsLength * sizeof(Vec3));
				}
			}

			hashTableFree(hashTable);

			free(indexedVertices);
			free(indexedUVs);
			free(indexedNormals);
			free(indexedIndices);
		}
	}

	/**
	 * If there was an error, send
	 * an empty model.
	 */
	if (error)
	{
		free(vertices);
		free(uvs);
		free(normals);
		free(indices);

		vertices = NULL;
		uvs = NULL;
		normals = NULL;
		indices = NULL;

		verticesLength = 0;
		uvsLength = 0;
		normalsLength = 0;
		indicesLength = 0;
	}

	Model *model = modelNew(vertices, uvs, normals, indices, verticesLength, uvsLength, normalsLength, indicesLength);

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

int modelObjProcessVec3(char *line, Vec3 *vector3)
{
	if (sscanf(line, "%*s%f %f %f", &vector3->x, &vector3->y, &vector3->z) == 3)
	{
		return 0;
	}

	return -1;
}

int modelObjProcessVec2(char *line, Vec2 *vector2)
{
	if (sscanf(line, "%*s%f %f", &vector2->x, &vector2->y) == 2)
	{
		return 0;
	}

	return -1;
}

int modelObjProcessFace(char *line, Vec3 *face1, Vec3 *face2, Vec3 *face3)
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