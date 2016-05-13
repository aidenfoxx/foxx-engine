#ifndef PROP_H
#define PROP_H

#include <stdio.h>

#include "context.h"
#include "glmath.h"
#include "Scene/asset.h"

typedef struct {
	GLuint vbo[4];
	GLuint ibo;
	Asset *asset;
	Vec3 scale;
	Vec3 rotation;
	Vec3 translation;
	Matrix matrix;
} Prop;

void propInit(Prop*, Asset*);
void propDestroy(Prop*);
void propRotate(Prop*, float, float, float);
void propTranslate(Prop*, float, float, float);
void propScale(Prop*, float, float, float);

#endif