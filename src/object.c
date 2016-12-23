#include "object.h"

void objectUpdateTransform(Object*);

Object *objectNew(Model *model, Texture *diffuse, Texture *specular, Texture *normal)
{
	Object *object;

	if ((object = malloc(sizeof(Object))) != NULL)
	{
		object->model = model;
		object->scale = vec3(1.0f, 1.0f, 1.0f);
		object->rotation = vec3(0.0f, 0.0f, 0.0f);
		object->translation = vec3(0.0f, 0.0f, 0.0f);

		objectSetModel(object, model);
		objectSetTexture(TEXTURE_DIFFUSE, object, diffuse);
		objectSetTexture(TEXTURE_SPECULAR, object, specular);
		objectSetTexture(TEXTURE_NORMAL, object, normal);
		objectUpdateTransform(object);
	}

	return object;
}

Object *objectDuplicate(Object *object)
{
	return objectNew(object->model, object->diffuse, object->specular, object->normal);
}

void objectFree(Object *object)
{
	if (object)
	{
		free(object);
	}
}

void objectSetModel(Object *object, Model *model)
{
	object->model = model;
}

void objectSetTexture(int textureType, Object *object, Texture *texture)
{
	switch (textureType)
	{
		case TEXTURE_DIFFUSE:
			object->diffuse = texture;
			break;

		case TEXTURE_SPECULAR:
			object->specular = texture;
			break;

		case TEXTURE_NORMAL:
			object->normal = texture;
			break;
	}
}

Model *objectGetModel(Object *object)
{
	return object->model;
}

Texture *objectGetTexture(int textureType, Object *object)
{
	switch (textureType)
	{
		case TEXTURE_DIFFUSE:
			return object->diffuse;

		case TEXTURE_SPECULAR:
			return object->specular;

		case TEXTURE_NORMAL:
			return object->normal;
	}
	return NULL;
}

void objectTranslate(Object *object, Vec3 translation)
{
	vec3AddVec3(object->translation, translation);
	objectUpdateTransform(object);
}

void objectRotate(Object *object, Vec3 rotate)
{
	vec3AddVec3(object->rotation, rotate);
	objectUpdateTransform(object);
}

void objectScale(Object *object, Vec3 scale)
{
	vec3AddVec3(object->scale, scale);
	objectUpdateTransform(object);
}

void objectSetTranslation(Object *object, Vec3 translation)
{
	object->translation = translation;
	objectUpdateTransform(object);
}

void objectSetRotation(Object *object, Vec3 rotate)
{
	object->rotation = rotate;
	objectUpdateTransform(object);
}

void objectSetScale(Object *object, Vec3 scale)
{
	object->scale = scale;
	objectUpdateTransform(object);
}

Vec3 objectGetTranslation(Object *object)
{
	return object->translation;
}

Vec3 objectGetRotation(Object *object)
{
	return object->rotation;
}

Vec3 objectGetScale(Object *object)
{
	return object->scale;
}

Mat4 objectGetTransform(Object *object)
{
	return object->transform;
}

void objectUpdateTransform(Object *object)
{
	Mat4 scale = mat4Scale(object->scale);
	Mat4 rotation  = mat4RotationQuat(eulerConvertQuat(object->rotation));
	Mat4 translation = mat4Translation(object->translation);

	object->transform = mat4MultiplyMat4(translation, mat4MultiplyMat4(scale, rotation));
}