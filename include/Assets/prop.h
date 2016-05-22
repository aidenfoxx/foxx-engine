#ifndef PROP_H
#define PROP_H

#include <stdio.h>

#include "context.h"
#include "glmath.h"
#include "asset.h"

typedef struct {
	GLuint vbo[4];
	Asset *asset;
	Vector3f scale;
	Vector3f rotation;
	Vector3f translation;
	Matrix4 matrix;
} Prop;

void propInit(Prop*, Asset*);
void propDestroy(Prop*);
void propRotate(Prop*, float, float, float);
void propTranslate(Prop*, float, float, float);
void propScale(Prop*, float, float, float);

#endif