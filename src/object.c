#include "object.h"

static void objectUpdateTransform(Object*);
static int objectSetParameter(Object*, const char*, void *);
static void *objectGetParameter(Object*, const char*);
static int objectParameterKey(const char*);

Object *objectNew(Model *model, Texture *diffuse, Texture *specular, Texture *normal)
{
	Object *object;

	if ((object = malloc(sizeof(Object))) != NULL)
	{
		object->model = model;
		object->scale = vec3(1.0f, 1.0f, 1.0f);
		object->rotation = vec4(0.0f, 0.0f, 0.0f, 0.0f);
		object->translation = vec3(0.0f, 0.0f, 0.0f);
		object->parameters = arrayNew();
		object->parametersIndex = hashTableNew(OBJECT_PARAMETER_MAX);

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
		for (int i = 0; i < arrayLength(object->parameters); i++)
		{
			free(arrayGet(object->parameters, i));
		}

		hashTableFree(object->parametersIndex);
		arrayFree(object->parameters);
		free(object);
	}
}

/**
 * Object data functions.
 */
void objectSetModel(Object *object, Model *model)
{
	object->model = model;
}

/**
 * TODO: Clean up consts
 */
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

int objectSetParameterInt(Object *object, const char *parameter, int data)
{
	int *parameterData = malloc(sizeof(int));
	memcpy(parameterData, &data, sizeof(int));
	return objectSetParameter(object, parameter, parameterData);
}

int objectSetParameterLong(Object *object, const char *parameter, long data)
{
	long *parameterData = malloc(sizeof(long));
	memcpy(parameterData, &data, sizeof(long));
	return objectSetParameter(object, parameter, parameterData);
}

int objectSetParameterFloat(Object *object, const char *parameter, float data)
{
	float *parameterData = malloc(sizeof(float));
	memcpy(parameterData, &data, sizeof(float));
	return objectSetParameter(object, parameter, parameterData);
}

int objectSetParameterString(Object *object, const char *parameter, char *data)
{
	char *parameterData = calloc(sizeof(char), strlen(data) + 1);
	strcpy(parameterData, data);
	return objectSetParameter(object, parameter, parameterData);
}

int objectSetParameterVec2(Object *object, const char *parameter, Vec2 data)
{
	Vec2 *parameterData = malloc(sizeof(Vec2));
	memcpy(parameterData, &data, sizeof(Vec2));
	return objectSetParameter(object, parameter, parameterData);
}

int objectSetParameterVec3(Object *object, const char *parameter, Vec3 data)
{
	Vec3 *parameterData = malloc(sizeof(Vec3));
	memcpy(parameterData, &data, sizeof(Vec3));
	return objectSetParameter(object, parameter, parameterData);
}

int objectSetParameterVec4(Object *object, const char *parameter, Vec4 data)
{
	Vec4 *parameterData = malloc(sizeof(Vec4));
	memcpy(parameterData, &data, sizeof(Vec4));
	return objectSetParameter(object, parameter, parameterData);
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

int objectGetParameterInt(Object *object, const char *parameter)
{
	int *data = (int*)objectGetParameter(object, parameter);
	return data != NULL ? *data : 0;
}

long objectGetParameterLong(Object *object, const char *parameter)
{
	long *data = (long*)objectGetParameter(object, parameter);
	return data != NULL ? *data : 0;
}

float objectGetParameterFloat(Object *object, const char *parameter)
{
	float *data = (float*)objectGetParameter(object, parameter);
	return data != NULL ? *data : 0.0f;
}

char *objectGetParameterString(Object *object, const char *parameter)
{
	char *data = (char*)objectGetParameter(object, parameter);
	return data != NULL ? data : NULL;
}

Vec2 objectGetParameterVec2(Object *object, const char *parameter)
{
	Vec2 *data = (Vec2*)objectGetParameter(object, parameter);
	return data != NULL ? *data : vec2(0.0f, 0.0f);
}

Vec3 objectGetParameterVec3(Object *object, const char *parameter)
{
	Vec3 *data = (Vec3*)objectGetParameter(object, parameter);
	return data != NULL ? *data : vec3(0.0f, 0.0f, 0.0f);
}

Vec4 objectGetParameterVec4(Object *object, const char *parameter)
{
	Vec4 *data = (Vec4*)objectGetParameter(object, parameter);
	return data != NULL ? *data : vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * Transformation functions.
 */
void objectTranslate(Object *object, Vec3 translation)
{
	vec3AddVec3(object->translation, translation);
	objectUpdateTransform(object);
}

void objectRotate(Object *object, Vec4 rotation)
{
	vec4AddVec4(object->rotation, rotation);
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

void objectSetRotation(Object *object, Vec4 rotation)
{
	object->rotation = rotation;
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

Vec4 objectGetRotation(Object *object)
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

/**
 * Math functions.
 */
Vec3 objectGetMinEdge(Object *object)
{
	Vec3 minEdge = vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < object->model->verticesLength; i++)
	{
		Vec3 vertex = object->model->vertices[i];

		minEdge.x = vertex.x < minEdge.x ? vertex.x : minEdge.x;
		minEdge.y = vertex.y < minEdge.y ? vertex.y : minEdge.y;
		minEdge.z = vertex.z < minEdge.z ? vertex.z : minEdge.z;
	}

	return minEdge;
}

Vec3 objectGetMaxEdge(Object *object)
{
	Vec3 maxEdge = vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < object->model->verticesLength; i++)
	{
		Vec3 vertex = object->model->vertices[i];

		maxEdge.x = vertex.x > maxEdge.x ? vertex.x : maxEdge.x;
		maxEdge.y = vertex.y > maxEdge.y ? vertex.y : maxEdge.y;
		maxEdge.z = vertex.z > maxEdge.z ? vertex.z : maxEdge.z;
	}

	return maxEdge;
}

Vec3 objectGetCenter(Object *object)
{
	Vec3 minEdge = objectGetMinEdge(object);
	Vec3 maxEdge = objectGetMaxEdge(object);

	return vec3DivideVec3(vec3AddVec3(minEdge, maxEdge), vec3(2.0f, 2.0f, 2.0f));
}

Vec3 objectGetBoundingBox(Object *object)
{
	Vec3 minEdge = objectGetMinEdge(object);
	Vec3 maxEdge = objectGetMaxEdge(object);

	return vec3AddVec3(minEdge, vec3Negative(maxEdge));
}

void objectUpdateTransform(Object *object)
{
	Mat4 scale = mat4Scale(object->scale);
	Mat4 rotation  = mat4RotationQuat(object->rotation);
	Mat4 translation = mat4Translation(object->translation);

	object->transform = mat4MultiplyMat4(translation, mat4MultiplyMat4(scale, rotation));
}

int objectSetParameter(Object *object, const char *parameter, void *data)
{
	if (hashTableSet(object->parametersIndex, objectParameterKey(parameter), arrayLength(object->parameters)))
	{
		return -1;
	}

	arrayPush(object->parameters, data);

	return 0;
}

void *objectGetParameter(Object *object, const char *parameter)
{
	int index;

	if ((index = hashTableGet(object->parametersIndex, objectParameterKey(parameter))) != -1)
	{
		return arrayGet(object->parameters, index);
	}

	return NULL;
}

int objectParameterKey(const char *parameter)
{
	int i = 0;
	int key = 0;

	while (parameter[i])
	{
		key = hashTableKey(key, parameter[i]);
		i++;
	}

	return key;
}