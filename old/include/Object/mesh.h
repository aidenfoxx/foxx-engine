#ifndef MESH_H
#define MESH_H

#include <stdio.h>
#include <stdlib.h>

#include "Tools/glmath.h"

typedef struct {
	int verticesLength;
	int uvsLength;
	int normalsLength;
	int indicesLength;
	Vector3f *vertices;
	Vector2f *uvs;
	Vector3f *normals;
	Vector3i *indices;
} Mesh;

void meshInit(Mesh*);
void meshDestroy(Mesh*);

#endif