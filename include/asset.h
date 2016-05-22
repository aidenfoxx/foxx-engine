#ifndef ASSET_H
#define ASSET_H

#include <stdio.h>
#include <stdlib.h>

#include "glmath.h"

#include "Assets/obj.h"
#include "Tools/hashtable.h"

typedef struct {
	int indicesCount;
	int indicesLength;
	Vector3f *vertices;
	Vector2f *uvs;
	Vector3f *normals;
	Vector3i *indices;
} Asset;

void assetInit(Asset*);
void assetDestroy(Asset*);
int assetBindObj(Asset*, Obj*);

#endif