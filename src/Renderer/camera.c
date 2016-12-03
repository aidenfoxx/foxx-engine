#include "Renderer/camera.h"

static Camera *cameraNew(Mat4);
static void cameraUpdateView(Camera*);

Camera *cameraNew(Mat4 projection)
{
	Camera *camera = NULL;

	if ((camera = malloc(sizeof(Camera))) != NULL)
	{
		camera->forward = vec3(0.0f, 0.0f, -1.0f);
		camera->up = vec3(0.0f, 1.0f, 0.0f);
		camera->right = vec3(1.0f, 0.0f, 0.0f);
		camera->rotation = vec3(0.0f, 0.0f, 0.0f);
		camera->translation = vec3(0.0f, 0.0f, 0.0f);
		camera->projection = projection;
		
		cameraUpdateView(camera);
	}

	return camera;
}

Camera *cameraPerspectiveNew(float fov, float aspectRatio)
{
	return cameraNew(mat4Perspective(fov, aspectRatio, 0.1f, 100.0f));
}

Camera *cameraOrthographicNew(float left, float right, float top, float bottom)
{
	return cameraNew(mat4Orthographic(left, right, top, bottom, 0.1f, 100.0f));
}

void cameraFree(Camera *camera)
{
	if (camera)
	{
		free(camera);
	}
}

void cameraTranslate(Camera *camera, Vec3 translation)
{
	Vec3 vecX = vec3(translation.x, translation.x, translation.x);
	Vec3 vecY = vec3(translation.y, translation.y, translation.y);
	Vec3 vecZ = vec3(translation.z, translation.z, translation.z);

	camera->translation = vec3AddVec3(camera->translation, vec3MultiplyVec3(camera->right, vecX));
	camera->translation = vec3AddVec3(camera->translation, vec3MultiplyVec3(camera->up, vecY));
	camera->translation = vec3AddVec3(camera->translation, vec3MultiplyVec3(camera->forward, vecZ));

	cameraUpdateView(camera);
}

void cameraRotate(Camera *camera, Vec3 rotation)
{
	camera->rotation = vec3AddVec3(camera->rotation, rotation);

	Mat4 rotationMatrix = mat4Inverse(mat4RotationEuler(camera->rotation));
	
	camera->forward = vec3Normalize(vec3MultiplyMat4(vec3(0.0f, 0.0f, -1.0f), rotationMatrix));
	camera->up = vec3Normalize(vec3MultiplyMat4(vec3(0.0f, 1.0f, 0.0f), rotationMatrix));
	camera->right = vec3Normalize(vec3MultiplyMat4(vec3(1.0f, 0.0f, 0.0f), rotationMatrix));
	
	cameraUpdateView(camera);
}

void cameraSetTranslation(Camera *camera, Vec3 translation)
{
	camera->translation = translation;
	cameraUpdateView(camera);
}

void cameraSetRotation(Camera *camera, Vec3 rotation)
{
	camera->rotation = rotation;
	cameraUpdateView(camera);
}

Vec3 cameraGetTranslation(Camera *camera)
{
	return camera->translation;
}

Vec3 cameraGetRotation(Camera *camera)
{
	return camera->rotation;
}

void cameraUpdateView(Camera *camera)
{
	Mat4 rotation = mat4RotationEuler(camera->rotation);
	Mat4 translation = mat4Translation(camera->translation);

	camera->view = mat4MultiplyMat4(rotation, translation);
}