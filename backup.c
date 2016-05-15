#include "Scene/asset.h"

static int assetParseObj(Asset*, char*, char*, int, int, int, int, int, int);

void assetInit(Asset *asset)
{
	asset->vertexData = NULL;
	asset->textureData = NULL;
	asset->normalData = NULL;
	asset->indexData = NULL;
	asset->vertexLength = 0;
	asset->textureLength = 0;
	asset->normalLength = 0;
	asset->indexLength = 0;
}

void assetDestroy(Asset *asset)
{
	free(asset->vertexData);
	free(asset->textureData);
	free(asset->normalData);
	free(asset->indexData);
}

int assetLoadObj(Asset *asset, const char *path)
{
	char lineData[128];

	FILE *file = fopen(path, "rb");
	
	if (!file)
	{
		return -1;
	}

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned int vertexLength = 0;
	unsigned int textureLength = 0;
	unsigned int normalLength = 0;
	unsigned int indexLength = 0;

	unsigned int vertexBufferLength = 0;
	unsigned int indexBufferLength = 0;
	char *vertexBuffer = malloc((length + 1) * sizeof(char));
	char *indexBuffer = malloc((length + 1) * sizeof(char));

	/**
	 * Read file line by line into associated
	 * buffers and count data sizes.
	 */
	while (fgets(lineData, sizeof(lineData), file) != NULL) 
	{ 
		int lineSize = strlen(lineData);

		if (lineData[0] == 'v')
		{
			memcpy(&vertexBuffer[vertexBufferLength], lineData, lineSize * sizeof(char));
			vertexBufferLength += lineSize;
			vertexBuffer[vertexBufferLength + 1] = '\0';

			if (lineData[1] == ' ')
			{
				vertexLength++;
			}
			else if (lineData[1] == 't' && lineData[2] == ' ')
			{
				textureLength++;
			}
			else if (lineData[1] == 'n' && lineData[2] == ' ')
			{
				normalLength++;
			}
		}
		else if (lineData[0] == 'f' && lineData[1] == ' ')
		{
			memcpy(&indexBuffer[indexBufferLength], lineData, lineSize * sizeof(char));
			indexBufferLength += lineSize;
			indexBuffer[indexBufferLength + 1] = '\0';

			indexLength++;
		}
	}

	vertexBuffer = realloc(vertexBuffer, (vertexBufferLength + 1) * sizeof(char));
	indexBuffer = realloc(indexBuffer, (indexBufferLength + 1) * sizeof(char));

	fclose(file);

	int parseError = assetParseObj(asset, vertexBuffer, indexBuffer, vertexBufferLength, indexBufferLength, vertexLength, textureLength, normalLength, indexLength);

	if (parseError == -1)
	{
		return -2;
	}
	else if (parseError == -2)
	{
		return -3;
	}

	return 0;
}

int assetParseObj(Asset *asset, char *vertexBuffer, char *indexBuffer, int vertexBufferLength, int indexBufferLength, int vertexLength, int textureLength, int normalLength, int indexLength)
{
	int returnError = 0;
	char lineData[128];
	unsigned int lineLength = 0;

	unsigned int vertexIndex = 0;
	unsigned int textureIndex = 0;
	unsigned int normalIndex = 0;
	unsigned int indexIndex = 0;

	unsigned int indexCount = 0;

	Vec3 *vertexData = malloc(vertexLength * sizeof(Vec3));
	Vec2 *textureData = malloc(textureLength * sizeof(Vec2));
	Vec3 *normalData = malloc(normalLength * sizeof(Vec3));
	Index *indexData = NULL;

	Vec3 tempVec3;
	Vec2 tempVec2;
	Index tempIndex[3];

	/**
	 * Load the vertex data into formatted variables.
	 */
	for (int i = 0; i < vertexBufferLength; i++)
	{
		if (vertexBuffer[i] == '\n')
		{
			if (lineLength > 127)
			{
				returnError = -1;
				lineLength = 0;
				break;
			}

			memcpy(lineData, &vertexData[i - lineLength], lineLength * sizeof(char));
			lineData[lineLength + 1] = '\0';
			lineLength = 0;

			if (lineData[0] == 'v')
			{
				if (lineData[1] == ' ')
				{
					if (sscanf(lineData, "%*s%f %f %f", &tempVec3.x, &tempVec3.y, &tempVec3.z) == 3)
					{
						vertexData[vertexIndex] = tempVec3;
						vertexIndex++;
						continue;
					}
				}
				else if (lineData[1] == 't' && lineData[2] == ' ')
				{
					if (sscanf(lineData, "%*s%f %f", &tempVec2.x, &tempVec2.y) == 2)
					{
						textureData[textureIndex] = tempVec2;
						textureIndex++;
						continue;
					}
				}
				else if (lineData[1] == 'n' && lineData[2] == ' ')
				{
					if (sscanf(lineData, "%*s%f %f %f", &tempVec3.x, &tempVec3.y, &tempVec3.z) == 3)
					{
						normalData[normalIndex] = tempVec3;
						normalIndex++;
						continue;
					}
				}
				returnError = -2;
			}
			continue;
		}
		lineLength++;
	}

	free(vertexBuffer);

	lineLength = 0;
	indexData = malloc((indexLength * 3) * sizeof(Index));

	/**
	 * Load the index data into formatted variables
	 * and count the number of indexes.
	 */
	for (int i = 0; i < indexBufferLength; i++)
	{
		if (indexBuffer[i] == '\n')
		{
			if (lineLength > 127)
			{
				returnError = -1;
				lineLength = 0;
				break;
			}

			memcpy(lineData, &indexBuffer[i - lineLength], lineLength * sizeof(char));
			lineData[lineLength + 1] = '\0';
			lineLength = 0;

			if (lineData[0] == 'f')
			{
				int count = sscanf(lineData, "%*s%u/%u/%u %u/%u/%u %u/%u/%u", 
					&tempIndex[0].x, &tempIndex[0].y, &tempIndex[0].z,
					&tempIndex[1].x, &tempIndex[1].y, &tempIndex[1].z,
					&tempIndex[2].x, &tempIndex[2].y, &tempIndex[2].z
				);

				/**
				 * Could we get all the data?
				 */
				if (count == 9)
				{
					indexData[indexIndex] = tempIndex[0];
					indexData[indexIndex + 1] = tempIndex[1];
					indexData[indexIndex + 2] = tempIndex[2];

					unsigned int v1Found, v2Found, v3Found;

					for (int i = 0; i < indexIndex; i++)
					{
						if (!v1Found && indexData[i].x == tempIndex[0].x && indexData[i].y == tempIndex[0].y && indexData[i].z == tempIndex[0].z)
						{
							v1Found = 1;
							indexCount--;
						}
						if (!v2Found && indexData[i].x == tempIndex[1].x && indexData[i].y == tempIndex[1].y && indexData[i].z == tempIndex[1].z)
						{
							v2Found = 1;
							indexCount--;
						}
						if (!v3Found && indexData[i].x == tempIndex[2].x && indexData[i].y == tempIndex[2].y && indexData[i].z == tempIndex[2].z)
						{
							v3Found = 1;
							indexCount--;
						}
					}

					indexIndex += 3;
					indexCount += 3;

					continue;
				}
				returnError = -2;
			}
			continue;
		}
		lineLength++;
	}

	free(indexBuffer);

	assetProcessObj(asset, vertexData, textureData, normalData, indexData, indexCount, indexLength);

	return returnError;
}

int assetProcessObj(Asset *asset, Vec3 *vertexData, Vec2 *texturelData, Vec3 *normalData, Vec3 *indexData, int indexCount, int indexLength)
{
	asset->vertexLength = indexCount;
	asset->textureLength = indexCount;
	asset->normalLength = indexCount;
	asset->indexLength = indexLength;

	asset->vertexData = malloc(indexCount * sizeof(Vec3));
	asset->textureData = malloc(indexCount * sizeof(Vec2));
	asset->normalData = malloc(indexCount * sizeof(Vec3));
	asset->indexData = malloc(indexLength * sizeof(Index));

	/**
	 * TODO: Sort this damn data.
	 */
	for (int i = 0; i < indexLength; i++)
	{
		int relativeIndex = i * 3;

		asset->vertexData[relativeIndex] = vertexData[indexData[relativeIndex].x];
		asset->textureData[relativeIndex] = textureData[indexData[relativeIndex].y];
		asset->normalData[relativeIndex] = normalData[indexData[relativeIndex].z];

		asset->vertexData[relativeIndex + 1] = vertexData[indexData[relativeIndex + 1].x];
		asset->textureData[relativeIndex + 1] = textureData[indexData[relativeIndex + 1].y];
		asset->normalData[relativeIndex + 1] = normalData[indexData[relativeIndex + 1].z];

		asset->vertexData[relativeIndex + 2] = vertexData[indexData[relativeIndex + 2].x];
		asset->textureData[relativeIndex + 2] = textureData[indexData[relativeIndex + 2].y];
		asset->normalData[relativeIndex + 2] = normalData[indexData[relativeIndex + 2].z];

		Index index = {  };

		asset->indexData[i] = 
	}

	free(vertexData);
	free(textureData);
	free(normalData);
	free(indexData);
}