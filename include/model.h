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
	GLuint vbo[4];
	Vec3 *vertices;
	Vec2 *uvs;
	Vec3 *normals;
	Vec3 *indices;
	int verticesLength;
	int uvsLength;
	int normalsLength;
	int indicesLength;
} Model;

Model *modelNew(Vec3*, Vec2*, Vec3*, Vec3*, int, int, int, int);
Model *modelDuplicate(Model*);
void modelFree(Model*);

void modelSetProperty(int, Model*, void*, int);
void *modelGetProperty(int, Model*);
int modelGetPropertyLength(int, Model*);

void modelBindProperty(int, Model*);
void modelUnbind();

#endif