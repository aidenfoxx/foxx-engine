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
	Vec3 *vertices;
	Vec2 *uvs;
	Vec3 *normals;
	Vec3 *indices;
} Obj;

int objToFem(uint8_t*, uint8_t**);
int objProcess(uint8_t*, Obj**);

#endif