#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include <stdio.h>
#include <stdlib.h>

#include "Tools/glmath.h"

typedef struct {
	Vec3 up;
	Vec3 forward;
	Vec3 right;
	Vec3 rotation;
	Vec3 translation;
	Mat4 projection;
	Mat4 view;
} Camera;

Camera *cameraPerspectiveNew(float, float);
Camera *cameraOrthographic(float, float, float, float);
void cameraFree(Camera*);

void cameraTranslate(Camera*, Vec3);
void cameraRotate(Camera*, Vec3);

void cameraSetTranslation(Camera*, Vec3);
void cameraSetRotation(Camera*, Vec3);
void cameraSetProjection(Camera*, Mat4);

Vec3 cameraGetTranslation(Camera*);
Vec3 cameraGetRotation(Camera*);
Mat4 cameraGetProjection(Camera*);
Mat4 cameraGetView(Camera*);

#endif