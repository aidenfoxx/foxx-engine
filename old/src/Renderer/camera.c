#include "Renderer/camera.h"

static void cameraUpdateView(Camera*);

void cameraInit(Camera *camera)
{
	camera->rotation = vector3f(0.0f, 0.0f, 0.0f);
	camera->translation = vector3f(0.0f, 0.0f, -5.0f);
	
	cameraUpdateView(camera);
	cameraPerspective(camera, 1.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

void cameraPerspective(Camera *camera, float fov, float aspectRatio, float nearClip, float farClip)
{
	camera->perspective = matrix4Perspective(fov, aspectRatio, nearClip, farClip);
}

void cameraOrthographic(Camera *camera, float left, float right, float bottom, float top, float nearClip, float farClip)
{
	camera->perspective = matrix4Orthographic(left, right, bottom, top, nearClip, farClip);
}

void cameraRotate(Camera *camera, float x, float y, float z)
{
	camera->rotation.x += x;
	camera->rotation.y += y;
	camera->rotation.z += z;

	cameraUpdateView(camera);
}

void cameraTranslate(Camera *camera, float x, float y, float z)
{
	camera->translation.x += x;
	camera->translation.y += y;
	camera->translation.z += z;

	cameraUpdateView(camera);
}

void cameraUpdateView(Camera *camera)
{
	Matrix4 rotationMatrix  = matrix4Quat(eulerConvertQuat(camera->rotation));
	Matrix4 translateMatrix = matrix4Translate(camera->translation);

	camera->view = matrix4MultiplyMatrix4(translateMatrix, rotationMatrix);
}