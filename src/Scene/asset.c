#include "Scene/asset.h"

static int assetParseObj(Asset*, char*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
static int assetProcessObj(Asset*, Vec3*, Vec2*, Vec3*, Index*, unsigned int, unsigned int);
static int assetIndexExist(Index*, Index*, unsigned int);

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

	char *buffer = malloc((length + 1) * sizeof(char));
	int bufferLength = 0;

	/**
	 * Read file line by line into associated
	 * buffers and count data sizes.
	 */
	while (fgets(lineData, sizeof(lineData), file) != NULL) 
	{
		if (lineData[0] == 'v' || lineData[0] == 'f')
		{
			memcpy(&buffer[bufferLength], lineData, strlen(lineData) * sizeof(char));
			bufferLength += strlen(lineData);
			buffer[bufferLength] = '\0';
		}

		if (lineData[0] == 'v')
		{
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
			indexLength++;
		}
	}

	fclose(file);

	buffer = realloc(buffer, (bufferLength + 1) * sizeof(char));

	int parseError = assetParseObj(asset, buffer, length, vertexLength, textureLength, normalLength, indexLength);

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

int assetParseObj(Asset *asset, char *buffer, unsigned int bufferLength, unsigned int vertexLength, unsigned int textureLength, unsigned int normalLength, unsigned int indexLength)
{
	int returnError = 0;
	char lineData[128];
	unsigned int lineLength = 0;

	unsigned int vertexIndex = 0;
	unsigned int textureIndex = 0;
	unsigned int normalIndex = 0;
	unsigned int indexIndex = 0;

	unsigned int indexCount = indexLength * 3;

	Vertex *vertexData = malloc(vertexLength * sizeof(Vec3));
	Texture *textureData = malloc(textureLength * sizeof(Vec2));
	Normal *normalData = malloc(normalLength * sizeof(Vec3));
	Index *indexData = malloc((indexLength * 3) * sizeof(Index));

	Vec3 tempVec3;
	Vec2 tempVec2;
	Index tempIndex[3];

	/**
	 * Load the vertex data into formatted variables.
	 *
	 * TODO:
	 * http://stackoverflow.com/questions/17983005/c-how-to-read-a-string-line-by-line
	 */
	for (int i = 0; i < bufferLength; i++)
	{
		if (buffer[i] == '\n' || i == bufferLength - 1)
		{
			if (lineLength > 127)
			{
				returnError = -1;
				lineLength = 0;
				break;
			}

			memcpy(lineData, &buffer[i - lineLength], lineLength * sizeof(char));
			lineData[lineLength] = '\0';
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
			else if (lineData[0] == 'f')
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
					if (assetIndexExist(indexData, &tempIndex[0], indexIndex) > -1)
					{
						indexCount--;
					}

					indexData[indexIndex] = tempIndex[0];

					if (assetIndexExist(indexData, &tempIndex[1], indexIndex + 1) > -1)
					{
						indexCount--;
					}

					indexData[indexIndex + 1] = tempIndex[1];

					if (assetIndexExist(indexData, &tempIndex[2], indexIndex + 2) > -1)
					{
						indexCount--;
					}

					indexData[indexIndex + 2] = tempIndex[2];

					indexIndex += 3;

					continue;
				}
				returnError = -2;
			}
			continue;
		}
		lineLength++;
	}

	free(buffer);

	assetProcessObj(asset, vertexData, textureData, normalData, indexData, indexCount, indexLength);

	return returnError;
}

int assetProcessObj(Asset *asset, Vertex *vertexData, Texture *textureData, Normal *normalData, Index *indexData, unsigned int indexCount, unsigned int indexLength)
{
	asset->vertexLength = indexCount;
	asset->textureLength = indexCount;
	asset->normalLength = indexCount;
	asset->indexLength = indexLength;

	asset->vertexData = malloc(asset->vertexLength * sizeof(Vertex));
	asset->textureData = malloc(asset->textureLength * sizeof(Texture));
	asset->normalData = malloc(asset->normalLength * sizeof(Normal));
	asset->indexData = malloc(asset->indexLength * sizeof(Index));

	int *indexArray = (int*) asset->indexData;
	int indexCurrent = 0;

	for (int i = 0; i < indexLength * 3; i++)
	{
		int duplicateID;

		if ((duplicateID = assetIndexExist(indexData, &indexData[i], i)) < 0)
		{
			asset->vertexData[indexCurrent] = vertexData[indexData[i].x - 1];
			asset->textureData[indexCurrent] = textureData[indexData[i].y - 1];
			asset->normalData[indexCurrent] = normalData[indexData[i].z - 1];

			indexArray[i] = indexCurrent;

			indexCurrent++;
		}
		else
		{
			indexArray[i] = indexArray[duplicateID];
		}
	}

	free(vertexData);
	free(textureData);
	free(normalData);
	free(indexData);

	return 0;
}

int assetIndexExist(Index *indices, Index *comparison, unsigned int indexLength)
{
	for (int i = 0; i < indexLength; i++)
	{
		if (indices[i].x == comparison->x && indices[i].y == comparison->y && indices[i].z == comparison->z)
		{
			return i;
		}
	}
	return -1;
}