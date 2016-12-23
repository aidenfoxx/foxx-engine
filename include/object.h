#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "context.h"
#include "model.h"
#include "texture.h"
#include "Tools/glmath.h"

typedef struct {
	Model *model;
	Texture *diffuse;
	Texture *normal;
	Texture *specular;
	Vec3 scale;
	Vec3 rotation;
	Vec3 translation;
	Mat4 transform;
} Object;

Object *objectNew(Model*, Texture*, Texture*, Texture*);
Object *objectDuplicate(Object*);
void objectFree(Object*);

void objectSetModel(Object*, Model*);
void objectSetTexture(int, Object*, Texture*);

Model *objectGetModel(Object*);
Texture *objectGetTexture(int, Object*);

void objectTranslate(Object*, Vec3);
void objectRotate(Object*, Vec3);
void objectScale(Object*, Vec3);

void objectSetTranslation(Object*, Vec3);
void objectSetRotation(Object*, Vec3);
void objectSetScale(Object*, Vec3);

Vec3 objectGetTranslation(Object*);
Vec3 objectGetRotation(Object*);
Vec3 objectGetScale(Object*);
Mat4 objectGetTransform(Object*);

#endif