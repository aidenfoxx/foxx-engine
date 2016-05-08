#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include "glmath.h"

typedef struct {
	float fov;
	float aspectRatio;
	float nearClip;
	float farClip;
	Vec3 scale;
	Vec3 rotation;
	Vec3 translation;
	Matrix perspective;
	Matrix view;
} Camera;

void cameraInit(Camera*);
void cameraDestroy(Camera*);
void cameraSetPerspective(Camera*, float, float, float, float);
void cameraRotate(Camera*, float, float, float);
void cameraTranslate(Camera*, float, float, float);
void cameraScale(Camera*, float, float, float);

#endif