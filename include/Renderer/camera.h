#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include "Tools/glmath.h"

typedef struct {
	Vector3f rotation;
	Vector3f translation;
	Matrix4 perspective;
	Matrix4 view;
} Camera;

void cameraInit(Camera*);
void cameraDestroy(Camera*);
void cameraPerspective(Camera*, float, float, float, float);
void cameraOrthographic(Camera*, float, float, float, float, float, float);
void cameraRotate(Camera*, float, float, float);
void cameraTranslate(Camera*, float, float, float);

#endif