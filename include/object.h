#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdint.h>

#include "context.h"
#include "Tools/glmath.h"

#define OBJECT_DYNAMIC 0
#define OBJECT_STATIC 1

#define TEXTURE_DIFFUSE 0
#define TEXTURE_NORMAL 1
#define TEXTURE_SPECULAR 2

typedef struct {
	GLuint vbo[4];
	int verticesLength;
	int uvsLength;
	int normalsLength;
	int indicesLength;
	char *diffuse;
	char *normal;
	char *specular;
	Vec3 scale;
	Vec3 rotation;
	Vec3 translation;
	Mat4 transformMatrix;
} Object;

Object *objectNew();
void objectFree(Object*);

void objectTranslate(Object*, Vec3);
void objectRotate(Object*, Vec3);
void objectScale(Object*, Vec3);

void objectSetTranslation(Object*, Vec3);
void objectSetRotation(Object*, Vec3);
void objectSetScale(Object*, Vec3);

Vec3 objectGetTranslation(Object*);
Vec3 objectGetRotation(Object*);
Vec3 objectGetScale(Object*);

void objectUpdateModel(Object*, int, int, int, int, Vec3*, Vec2*, Vec3*, Vec3*);
void objectUpdateTexture(int, Object*, char*);
void objectUpdateMatrix(Object*);

#endif