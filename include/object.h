#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdint.h>

#include "context.h"
#include "model.h"
#include "texture.h"
#include "Tools/glmath.h"

#define TEXTURE_DIFFUSE 0
#define TEXTURE_NORMAL 1
#define TEXTURE_SPECULAR 2

typedef struct {
	int verticesLength;
	int uvsLength;
	int normalsLength;
	int indicesLength;
	GLuint vbo[4];
	GLuint diffuse;
	GLuint normal;
	GLuint specular;
	Vec3 scale;
	Vec3 rotation;
	Vec3 translation;
	Mat4 transformMatrix;
} Object;

Object *objectNew(Model*, Texture*, Texture*, Texture*);
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

void objectUpdateModel(Object*, Model*);
void objectUpdateTexture(int, Object*, Texture*);
void objectUpdateMatrix(Object*);

#endif