#ifndef ASSET_H
#define ASSET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "glmath.h"
#include "Tools/array.h"

typedef Vec3 Vertex;
typedef Vec2 Texture;
typedef Vec3 Normal;
typedef struct {
	unsigned int x;
	unsigned int y;
	unsigned int z;
} Index;

typedef struct {
	int vertexLength;
	int textureLength;
	int normalLength;
	int indexLength;
	Vertex *vertexData;
	Texture *textureData;
	Normal *normalData;
	Index *indexData;
} Asset;

void assetInit(Asset*);
void assetDestroy(Asset*);
int assetLoadObj(Asset*, const char*);

#endif