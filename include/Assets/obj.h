#ifndef OBJ_H
#define OBJ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glmath.h"

typedef struct {
	int verticesLength;
	int uvsLength;
	int normalsLength;
	int indicesLength;
	Vector3f *vertices;
	Vector2f *uvs;
	Vector3f *normals;
	Vector3i *indices;
} Obj;

int objInit(Obj*, const char*);
void objDestroy(Obj*);

#endif