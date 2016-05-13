#include "Scene/asset.h"

static int assetObjLength(Asset*, char*, int);
static int assetObjData(Asset*, char*, int);
static int assetObjLineData(Asset*, char*, int*, int*, int*, int*);
static int assetLoadFile(const char*, char**);

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
	char *assetData = NULL;
	long assetDataLength = assetLoadFile(path, &assetData);

	if (assetDataLength < 0)
	{
		return -1;
	}

	if (assetObjLength(asset, assetData, assetDataLength) || assetObjData(asset, assetData, assetDataLength))
	{
		return -2;
	}

	return 0;
}

int assetObjLength(Asset *asset, char *assetData, int assetDataLength)
{
	int returnError = 0;

	char *assetLine = malloc(129 * sizeof(char));
	int assetLineLength = 0;

	for (int i = 0; i < assetDataLength; i++)
	{
		if (assetData[i] == '\n')
		{
			if (assetLineLength >= 128)
			{
				returnError = -1;
				break;
			}

			memcpy(assetLine, &assetData[i - assetLineLength], assetLineLength * sizeof(char));
			assetLine[assetLineLength + 1] = '\0';
			assetLineLength = 0;

			if (assetLine[0] == 'v')
			{
				if (assetLine[1] == ' ')
				{
					asset->vertexLength++;
				}
				else if (assetLine[1] == 't' && assetLine[2] == ' ')
				{
					asset->textureLength++;
				}
				else if (assetLine[1] == 'n' && assetLine[2] == ' ')
				{
					asset->normalLength++;
				}
			}
			else if (assetLine[0] == 'f' && assetLine[1] == ' ')
			{
				asset->indexLength++;
			}
			continue;
		}
		assetLineLength++;
	}

	free(assetLine);

	return returnError;
}

int assetObjData(Asset *asset, char *assetData, int assetDataLength)
{
	int returnError = 0;

	int vertexIndex = 0;
	int textureIndex = 0;
	int normalIndex = 0;
	int indexIndex = 0;

    asset->vertexData = realloc(asset->vertexData, asset->vertexLength * sizeof(Vertex));
    asset->textureData = realloc(asset->textureData, asset->textureLength * sizeof(Texture));
    asset->normalData = realloc(asset->normalData, asset->normalLength * sizeof(Normal));
    asset->indexData = realloc(asset->indexData, asset->indexLength * sizeof(Index));

	char *assetLine = malloc(129 * sizeof(char));
	int assetLineLength = 0;
	
	for (int i = 0; i < assetDataLength; i++)
	{
		if (assetData[i] == '\n')
		{
			if (assetLineLength >= 128)
			{
				returnError = -1;
				break;
			}

			memcpy(assetLine, &assetData[i - assetLineLength], assetLineLength * sizeof(char));
			assetLine[assetLineLength + 1] = '\0';
			assetLineLength = 0;

			if (assetObjLineData(asset, assetLine, &vertexIndex, &textureIndex, &normalIndex, &indexIndex))
			{
				returnError = -2;
			}
			continue;
		}
		assetLineLength++;
	}

	free(assetLine);

	return returnError;
}

int assetObjLineData(Asset *asset, char *assetLine, int *vIndex, int *tIndex, int *nIndex, int *iIndex)
{
	if (assetLine[0] == 'v')
	{
		if (assetLine[1] == ' ')
		{
			float x, y, z;

			if (sscanf(assetLine, "%*s%f %f %f", &x, &y, &z) == 3)
			{
				asset->vertexData[*vIndex].x = x;
				asset->vertexData[*vIndex].y = y;
				asset->vertexData[*vIndex].z = z;
				(*vIndex)++;
				return 0;
			}
			return -1;
		}
		else if (assetLine[1] == 't' && assetLine[2] == ' ')
		{
			float x, y;

			if (sscanf(assetLine, "%*s%f %f", &x, &y) == 2)
			{
				asset->textureData[*tIndex].x = x;
				asset->textureData[*tIndex].y = y;
				(*tIndex)++;
				return 0;
			}
			return -1;
		}
		else if (assetLine[1] == 'n' && assetLine[2] == ' ')
		{
			float x, y, z;

			if (sscanf(assetLine, "%*s%f %f %f", &x, &y, &z) == 3)
			{
				asset->normalData[*nIndex].x = x;
				asset->normalData[*nIndex].y = y;
				asset->normalData[*nIndex].z = z;
				(*nIndex)++;
				return 0;
			}
			return -1;
		}
	}
	else if (assetLine[0] == 'f' && assetLine[1] == ' ')
	{
		unsigned int x, y, z;

		if (sscanf(assetLine, "%*s%u/%*u/%*u %u/%*u/%*u %u/%*u/%*u", &x, &y, &z) == 3)
		{
			asset->indexData[*iIndex].x = x - 1;
			asset->indexData[*iIndex].y = y - 1;
			asset->indexData[*iIndex].z = z - 1;
			(*iIndex)++;
			return 0;
		}
		return -1;
	}

	return 0;
}

int assetLoadFile(const char *assetPath, char **assetData)
{
	FILE *asset = fopen(assetPath, "rb");

	if (!asset)
	{
		return -1;
	}

	fseek(asset, 0, SEEK_END);
	int length = ftell(asset);
	fseek(asset, 0, SEEK_SET);

	*assetData = calloc(length + 1, 1);

	if (length != fread(*assetData, 1, length, asset)) 
	{ 
		free(*assetData);
		return -2;
	}

	fclose(asset);

	return length;
}