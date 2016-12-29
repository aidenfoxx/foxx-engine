#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "context.h"
#include "Tools/glmath.h"

#define MODEL_VERTICES 0
#define MODEL_UVS 1
#define MODEL_NORMALS 2
#define MODEL_INDICES 3

typedef struct {
	Vec3 *vertices;
	Vec2 *uvs;
	Vec3 *normals;
	int *indices;
	int verticesLength;
	int uvsLength;
	int normalsLength;
	int indicesLength;
} Model;

Model *modelNew(Vec3*, Vec2*, Vec3*, int*, int, int, int, int);
void modelFree(Model*);

#endif