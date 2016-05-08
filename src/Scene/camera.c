#include "Scene/camera.h"

static void cameraUpdateView(Camera*);

void cameraInit(Camera *camera)
{
	camera->scale = vec3New(1.0f, 1.0f, 1.0f);
	camera->rotation = vec3New(0.0f, 0.0f, 0.0f);
	camera->translation = vec3New(0.0f, 0.0f, -5.0f);
	
	cameraUpdateView(camera);
	cameraSetPerspective(camera, 1.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

void cameraSetPerspective(Camera *camera, float fov, float aspectRatio, float nearClip, float farClip)
{
	camera->fov = fov;
	camera->aspectRatio = aspectRatio;
	camera->nearClip = nearClip;
	camera->farClip = farClip;

	camera->perspective = matrixPerspective(fov, aspectRatio, nearClip, farClip);
}

void cameraScale(Camera *camera, float x, float y, float z)
{
	camera->scale.x *= x;
	camera->scale.y *= y;
	camera->scale.z *= z;

	cameraUpdateView(camera);
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
	Matrix scaleMatrix = matrixScale(camera->scale);
	Matrix rotationMatrix  = matrixRotateQuat(eulerConvertQuat(camera->rotation));
	Matrix translateMatrix = matrixTranslate(camera->translation);

	camera->view = matrixMultiplyMatrix(translateMatrix, matrixMultiplyMatrix(scaleMatrix, rotationMatrix));
}