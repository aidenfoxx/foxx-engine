#include "renderer/camera.h"

/**
 * TODD: COnvert to quaternain.
 */
Camera *cameraNew(Mat4 projection)
{
	Camera *camera = malloc(sizeof(Camera));

	camera->lockX = 0;
	camera->lockY = 0;
	camera->lockZ = 0;
	camera->right = vec3(1.0f, 0.0f, 0.0f);
	camera->up = vec3(0.0f, 1.0f, 0.0f);
	camera->forward = vec3(0.0f, 0.0f, -1.0f);
	camera->translation = vec3(0.0f, 0.0f, -10.0f);
	camera->rotation = vec3(0.0f, 0.0f, 0.0f);
	camera->transform = mat4MultiplyMat4(
		mat4Translation(camera->translation),
		mat4RotationEuler(camera->rotation)
	);
	camera->projection = projection;

	return camera;
}

void cameraFree(Camera *camera)
{
	assert(camera != NULL);
	free(camera);
}

void cameraLockAxisX(Camera *camera)
{
	camera->lockX = 1;
}

void cameraUnlockAxisX(Camera *camera)
{
	camera->lockX = 0;
}

void cameraLockAxisY(Camera *camera)
{
	camera->lockY = 1;
}

void cameraUnlockAxisY(Camera *camera)
{
	camera->lockY = 0;
}

void cameraLockAxisZ(Camera *camera)
{
	camera->lockZ = 1;
}

void cameraUnlockAxisZ(Camera *camera)
{
	camera->lockZ = 0;
}

Vec3 cameraGetTranslation(Camera *camera)
{
	return camera->translation;
}

/**
 * TODO: The issue with multiplying the transform matrix
 * by the transform matrix is the original transform doubles up!!
 */
void cameraSetTranslation(Camera *camera, Vec3 translation)
{
	camera->translation = translation;
	camera->transform = mat4MultiplyMat4(
		mat4Translation(camera->translation),
		mat4RotationEuler(camera->rotation)
	);
}

void cameraAddTranslation(Camera *camera, Vec3 translation)
{
	/**
	 * TODO: If you look down when lock is on your movement is slowed.
	 */
	Vec3 vecX = vec3(camera->lockX ? 0.0f : translation.x, camera->lockY ? 0.0f : translation.x, camera->lockZ ? 0.0f : translation.x);
	Vec3 vecY = vec3(camera->lockX ? 0.0f : translation.y, camera->lockY ? 0.0f : translation.y, camera->lockZ ? 0.0f : translation.y);
	Vec3 vecZ = vec3(camera->lockX ? 0.0f : -translation.z, camera->lockY ? 0.0f : -translation.z, camera->lockZ ? 0.0f : -translation.z);

	camera->translation = vec3AddVec3(camera->translation, vec3MultiplyVec3(camera->right, vecX));
	camera->translation = vec3AddVec3(camera->translation, vec3MultiplyVec3(camera->up, vecY));
	camera->translation = vec3AddVec3(camera->translation, vec3MultiplyVec3(camera->forward, vecZ));

	camera->transform = mat4MultiplyMat4(
		mat4Translation(camera->translation),
		mat4RotationEuler(camera->rotation)
	);
}

Vec3 cameraGetRotation(Camera *camera)
{
	return camera->rotation;
}

void cameraSetRotation(Camera *camera, Vec3 rotation)
{
	camera->rotation = rotation;
	camera->transform = mat4MultiplyMat4(
		mat4Translation(camera->translation),
		mat4RotationEuler(camera->rotation)
	);
	camera->right = vec3(camera->transform.xx, camera->transform.yx, camera->transform.zx);
	camera->up = vec3(camera->transform.xy, camera->transform.yy, camera->transform.zy);
	camera->forward = vec3(-camera->transform.xz, -camera->transform.yz, -camera->transform.zz);
}

void cameraAddRotation(Camera *camera, Vec3 rotation)
{
	camera->rotation = vec3AddVec3(camera->rotation, rotation);
	camera->transform = mat4MultiplyMat4(
		mat4Translation(camera->translation),
		mat4RotationEuler(camera->rotation)
	);
	camera->right = vec3(camera->transform.xx, camera->transform.yx, camera->transform.zx);
	camera->up = vec3(camera->transform.xy, camera->transform.yy, camera->transform.zy);
	camera->forward = vec3(-camera->transform.xz, -camera->transform.yz, -camera->transform.zz);
}

void cameraLookAt(Camera *camera, Vec3 target)
{
	/**
	 * We don't need to invert translation since
	 * we actually want the position.
	 */
	Vec3 direction = vec3Normalize(vec3AddVec3(target, camera->translation));

	float pitch = asin(direction.y);
	float yaw = atan2(-direction.x, -direction.z);

	cameraSetRotation(camera, vec3(pitch, yaw, 0.0f));
}