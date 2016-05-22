#include "asset.h"

void assetInit(Asset *asset)
{
	asset->indicesCount = 0;
	asset->indicesLength = 0;

	asset->vertices = NULL;
	asset->uvs = NULL;
	asset->normals = NULL;
	asset->indices = NULL;
}

void assetDestroy(Asset *asset)
{
	free(asset->vertices);
	free(asset->uvs);
	free(asset->normals);
	free(asset->indices);
}

int assetBindObj(Asset *asset, Obj *obj)
{
	int returnError = 0;

	asset->indicesCount = obj->indicesLength;
	asset->indicesLength = obj->indicesLength / 3;

	asset->vertices = malloc(asset->indicesCount * sizeof(Vector3f));
	asset->uvs = malloc(asset->indicesCount * sizeof(Vector2f));
	asset->normals = malloc(asset->indicesCount * sizeof(Vector3f));
	asset->indices = malloc(asset->indicesLength * sizeof(Vector3i));

	HashTable hashTable;
	hashTableInit(&hashTable, obj->indicesLength * 4);

	int *indexArray = (int*) asset->indices;
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
				asset->vertices[indexCount] = obj->vertices[obj->indices[i].x - 1];
			}
			else if (obj->indices[i].x < 0)
			{
				asset->vertices[indexCount] = obj->vertices[obj->verticesLength + obj->indices[i].x];
			}
			else
			{
				returnError = -1;
				break;
			}

			if (obj->indices[i].y > 0)
			{
				asset->uvs[indexCount] = obj->uvs[obj->indices[i].y - 1];
			}
			else if (obj->indices[i].y < 0)
			{
				asset->uvs[indexCount] = obj->uvs[obj->uvsLength + obj->indices[i].y];
			}
			else
			{
				asset->uvs[indexCount] = vector2f(0.0f, 0.0f);
			}

			if (obj->indices[i].z > 0)
			{
				asset->normals[indexCount] = obj->normals[obj->indices[i].z - 1];
			}
			else if (obj->indices[i].z < 0)
			{
				asset->normals[indexCount] = obj->normals[obj->normalsLength + obj->indices[i].z];
			}
			else
			{
				asset->normals[indexCount] = asset->vertices[indexCount];
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

	if (indexCount < obj->indicesLength)
	{
		asset->indicesCount = indexCount;

		asset->vertices = realloc(asset->vertices, indexCount * sizeof(Vector3f));
		asset->uvs = realloc(asset->uvs, indexCount * sizeof(Vector2f));
		asset->normals = realloc(asset->normals, indexCount * sizeof(Vector3f));
	}

	return returnError;
}