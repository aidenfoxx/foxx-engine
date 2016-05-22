#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include "glmath.h"

typedef struct {
	float fov;
	float aspectRatio;
	float nearClip;
	float farClip;
	Vector3f rotation;
	Vector3f translation;
	Matrix4 perspective;
	Matrix4 view;
} Camera;

void cameraInit(Camera*);
void cameraDestroy(Camera*);
void cameraRotate(Camera*, float, float, float);
void cameraTranslate(Camera*, float, float, float);
void cameraSetPerspective(Camera*, float, float, float, float);

#endif