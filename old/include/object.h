#ifndef OBJECT_H
#define OBJECT_H

#define OBJECT_DYNAMIC 0
#define OBJECT_STATIC 1

#include <stdio.h>

#include "context.h"
#include "Object/mesh.h"
#include "Object/texture.h"
#include "Tools/glmath.h"

typedef struct {
	GLuint vbo[4];
	Mesh *mesh;
	Texture *diffuse;
	Texture *specular;
	Texture *normal;
	Vector3f scale;
	Vector3f rotation;
	Vector3f translation;
	Matrix4 transformMatrix;
} Object;

void objectInit(Object*, Mesh*, Texture*, Texture*, Texture*);
void objectDestroy(Object*);

void objectRotate(Object*, float, float, float);
void objectTranslate(Object*, float, float, float);
void objectScale(Object*, float, float, float);

void objectUpdateMatrix(Object*);
void objectUpdateMesh(Object*, Mesh*);
void objectUpdateDiffuse(Object*, Texture*);
void objectUpdateSpecular(Object*, Texture*);
void objectUpdateNormal(Object*, Texture*);

#endif