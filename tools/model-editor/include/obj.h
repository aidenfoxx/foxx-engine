#ifndef OBJ_H
#define OBJ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Tools/glmath.h"
#include "Tools/hashtable.h"

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

int objToFem(uint8_t*, uint8_t**);
int objProcess(uint8_t*, Obj**);

#endif