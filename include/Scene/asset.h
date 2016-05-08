#ifndef ASSET_H
#define ASSET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int vertexLength;
	int uvLength;
	int normalLength;
	int indexLength;
	float *vertexData;
	float *uvData;
	float *normalData;
	float *indexData;
} Asset;

void assetInit(Asset*);
void assetLoadObj(Asset*, const char*);
void assetDestroy(Asset*);

#endif