#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "context.h"
#include "model.h"
#include "texture.h"
#include "Tools/array.h"
#include "Tools/hashtable.h"
#include "Tools/glmath.h"

#define OBJECT_PARAMETER_MAX 512
 
typedef struct {
	Model *model;
	Texture *diffuse;
	Texture *normal;
	Texture *specular;
	Vec3 scale;
	Vec4 rotation;
	Vec3 translation;
	Mat4 transform;
	Array *parameters;
	HashTable *parametersIndex;
} Object;

Object *objectNew(Model*, Texture*, Texture*, Texture*);
Object *objectDuplicate(Object*);
void objectFree(Object*);

void objectSetModel(Object*, Model*);
void objectSetTexture(int, Object*, Texture*);
int objectSetParameterInt(Object*, const char*, int);
int objectSetParameterLong(Object*, const char*, long);
int objectSetParameterFloat(Object*, const char*, float);
int objectSetParameterString(Object*, const char*, char*);
int objectSetParameterVec2(Object*, const char*, Vec2);
int objectSetParameterVec3(Object*, const char*, Vec3);
int objectSetParameterVec4(Object*, const char*, Vec4);

Model *objectGetModel(Object*);
Texture *objectGetTexture(int, Object*);
int objectGetParameterInt(Object*, const char*);
long objectGetParameterLong(Object*, const char*);
float objectGetParameterFloat(Object*, const char*);
char *objectGetParameterString(Object*, const char*);
Vec2 objectGetParameterVec2(Object*, const char*);
Vec3 objectGetParameterVec3(Object*, const char*);
Vec4 objectGetParameterVec4(Object*, const char*);

void objectTranslate(Object*, Vec3);
void objectRotate(Object*, Vec4);
void objectScale(Object*, Vec3);

void objectSetTranslation(Object*, Vec3);
void objectSetRotation(Object*, Vec4);
void objectSetScale(Object*, Vec3);

Vec3 objectGetTranslation(Object*);
Vec4 objectGetRotation(Object*);
Vec3 objectGetScale(Object*);
Mat4 objectGetTransform(Object*);

Vec3 objectGetMinEdge(Object*);
Vec3 objectGetMaxEdge(Object*);
Vec3 objectGetCenter(Object*);
Vec3 objectGetBoundingBox(Object*);

#endif