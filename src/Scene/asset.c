#include "Scene/asset.h"

static int assetParseObj(Asset*, char*, unsigned int, unsigned int, unsigned int, unsigned int);
static int assetProcessObj(Asset*, Vec3*, Vec2*, Vec3*, Index*, unsigned int, unsigned int);
static int assetIndexExist(Index*, Index*, unsigned int);
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
	unsigned int vertexLength = 0;
	unsigned int textureLength = 0;
	unsigned int normalLength = 0;
	unsigned int indexLength = 0;

	char *buffer = NULL;
	assetLoadFile(path, &buffer);
	char *currentLine = buffer;

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
				vertexLength++;
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				textureLength++;
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				normalLength++;
			}
		}
		else if (currentLine[0] == 'f' && currentLine[1] == ' ')
		{
			indexLength++;
		}

		if (nextLine)
		{
			*nextLine = '\n'; 
		}

		currentLine = nextLine ? (nextLine + 1) : NULL;
   	}

	int parseError = assetParseObj(asset, buffer, vertexLength, textureLength, normalLength, indexLength);

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

int assetParseObj(Asset *asset, char *buffer, unsigned int vertexLength, unsigned int textureLength, unsigned int normalLength, unsigned int indexLength)
{
	int returnError = 0;
	
	Vertex *vertexData = malloc(vertexLength * sizeof(Vertex));
	Texture *textureData = malloc(textureLength * sizeof(Texture));
	Normal *normalData = malloc(normalLength * sizeof(Normal));
	Index *indexData = malloc((indexLength * 3) * sizeof(Index));

	unsigned int vi = 0;
	unsigned int ti = 0;
	unsigned int ni = 0;
	unsigned int ii = 0;

	unsigned int finalVertexLength = indexLength * 3;

	char *currentLine = buffer;

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
				Vertex vertex;

				if (sscanf(currentLine, "%*s%f %f %f", &vertex.x, &vertex.y, &vertex.z) == 3)
				{
					vertexData[vi] = vertex;
					vi++;
				}
				else
				{
					returnError = -2;
				}
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				Texture texture;

				if (sscanf(currentLine, "%*s%f %f", &texture.x, &texture.y) == 2)
				{
					textureData[ti] = texture;
					ti++;
				}
				else
				{
					returnError = -2;
				}
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				Normal normal;

				if (sscanf(currentLine, "%*s%f %f %f", &normal.x, &normal.y, &normal.z) == 3)
				{
					normalData[ni] = normal;
					ni++;
				}
				else
				{
					returnError = -2;
				}
			}
		}
		else if (currentLine[0] == 'f')
		{
			Index index[3];

			int count = sscanf(currentLine, "%*s%u/%u/%u %u/%u/%u %u/%u/%u", 
				&index[0].x, &index[0].y, &index[0].z,
				&index[1].x, &index[1].y, &index[1].z,
				&index[2].x, &index[2].y, &index[2].z
			);

			if (count == 9)
			{
				indexData[ii] = index[0];
				indexData[ii + 1] = index[1];
				indexData[ii + 2] = index[2];

				if (assetIndexExist(indexData, &index[0], ii) > -1)
				{
					finalVertexLength--;
				}

				if (assetIndexExist(indexData, &index[1], ii + 1) > -1)
				{
					finalVertexLength--;
				}

				if (assetIndexExist(indexData, &index[2], ii + 2) > -1)
				{
					finalVertexLength--;
				}

				ii += 3;
			}
			else
			{
				returnError = -2;
			}
		}

		if (nextLine)
		{
			*nextLine = '\n'; 
		}

		currentLine = nextLine ? (nextLine + 1) : NULL;
	}

	free(buffer);

	assetProcessObj(asset, vertexData, textureData, normalData, indexData, finalVertexLength, indexLength);

	return returnError;
}

int assetProcessObj(Asset *asset, Vertex *vertexData, Texture *textureData, Normal *normalData, Index *indexData, unsigned int vertexLength, unsigned int indexLength)
{
	asset->vertexLength = vertexLength;
	asset->textureLength = vertexLength;
	asset->normalLength = vertexLength;
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
