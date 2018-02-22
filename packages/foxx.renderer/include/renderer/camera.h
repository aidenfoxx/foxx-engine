#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gl/gl3w.h>

#include "core/math.h"

typedef struct {
	int lockX;
	int lockY;
	int lockZ;
	Vec3 right;
	Vec3 up;
	Vec3 forward;
	Vec3 translation;
	Vec3 rotation;
	Mat4 transform;
	Mat4 projection;
} Camera;

Camera *cameraNew(Mat4);
void cameraFree(Camera*);

void cameraLockAxisX(Camera*);
void cameraUnlockAxisX(Camera*);

void cameraLockAxisY(Camera*);
void cameraUnlockAxisY(Camera*);

void cameraLockAxisZ(Camera*);
void cameraUnlockAxisZ(Camera*);

Vec3 cameraGetTranslation(Camera*);
void cameraSetTranslation(Camera*, Vec3);
void cameraAddTranslation(Camera*, Vec3);

Vec3 cameraGetRotation(Camera*);
void cameraSetRotation(Camera*, Vec3);
void cameraAddRotation(Camera*, Vec3);

void cameraLookAt(Camera*, Vec3);

#endif