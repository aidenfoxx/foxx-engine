#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>

#include "Tools/glmath.h"

typedef struct {
	int verticesLength;
	int uvsLength;
	int normalsLength;
	int indicesLength;
	Vec3 *vertices;
	Vec2 *uvs;
	Vec3 *normals;
	Vec3 *indices;
} Model;

Model *modelNew(int, int, int, int, Vec3*, Vec2*, Vec3*, Vec3*);
void modelFree(Model*);

#endif