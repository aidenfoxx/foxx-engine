#include "object.h"

Object *objectNew()
{
	Object *object = NULL;

	if ((object = malloc(sizeof(Object))) != NULL)
	{
		glGenBuffers(4, object->vbo);

		object->verticesLength = 0;
		object->uvsLength = 0;
		object->normalsLength = 0;
		object->indicesLength = 0;

		object->diffuse = NULL;
		object->specular = NULL;
		object->normal = NULL;

		object->scale = vec3(1.0f, 1.0f, 1.0f);
		object->rotation = vec3(0.0f, 0.0f, 0.0f);
		object->translation = vec3(0.0f, 0.0f, 0.0f);

		objectUpdateMatrix(object);
	}

	return object;
}

Object *objectDuplicate(Object *object)
{
	Object *duplicate = NULL;

	if ((duplicate = malloc(sizeof(Object))) != NULL)
	{
		/**
		 * TODO: Copy textures.
		 */
		memcpy(duplicate, object, sizeof(Object));
	}

	return duplicate;
}

void objectFree(Object *object)
{
	if (object != NULL)
	{
		glDeleteBuffers(4, object->vbo);
		free(object->diffuse);
		free(object->specular);
		free(object->normal);
		free(object);
	}
}

void objectTranslate(Object *object, Vec3 translation)
{
	vec3AddVec3(object->translation, translation);
	objectUpdateMatrix(object);
}

void objectRotate(Object *object, Vec3 rotate)
{
	vec3AddVec3(object->rotation, rotate);
	objectUpdateMatrix(object);
}

void objectScale(Object *object, Vec3 scale)
{
	vec3AddVec3(object->scale, scale);
	objectUpdateMatrix(object);
}

void objectSetTranslation(Object *object, Vec3 translation)
{
	object->translation = translation;
	objectUpdateMatrix(object);
}

void objectSetRotation(Object *object, Vec3 rotate)
{
	object->rotation = rotate;
	objectUpdateMatrix(object);
}

void objectSetScale(Object *object, Vec3 scale)
{
	object->scale = scale;
	objectUpdateMatrix(object);
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

void objectUpdateModel(Object *object, 
					  int verticesLength, 
					  int uvsLength, 
					  int normalsLength, 
					  int indicesLength,
					  Vec3 *vertices,
					  Vec2 *uvs,
					  Vec3 *normals,
					  Vec3 *indices)
{
	object->verticesLength = verticesLength;
	object->uvsLength = uvsLength;
	object->normalsLength = normalsLength;
	object->indicesLength = indicesLength;

	glBindBuffer(GL_ARRAY_BUFFER, object->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(Vec3), (float*)vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, object->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, uvsLength * sizeof(Vec2), (float*)uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, object->vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, normalsLength * sizeof(Vec3), (float*)normals, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(Vec3), (int*)indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void objectUpdateTexture(int textureType, Object *object, char *texture)
{
	int textureLength = strlen(texture) + 1;

	switch (textureType)
	{
		case TEXTURE_DIFFUSE:
			object->diffuse = malloc(textureLength);
			memcpy(object->diffuse, texture, textureLength);
			break;

		case TEXTURE_NORMAL:
			object->normal = malloc(textureLength);
			memcpy(object->normal, texture, textureLength);
			break;

		case TEXTURE_SPECULAR:
			object->specular = malloc(textureLength);
			memcpy(object->specular, texture, textureLength);
			break;
	}
}

void objectUpdateMatrix(Object *object)
{
	Mat4 scaleMatrix = mat4Scale(object->scale);
	Mat4 rotationMatrix  = mat4RotationQuat(eulerConvertQuat(object->rotation));
	Mat4 translateMatrix = mat4Translation(object->translation);

	object->transformMatrix = mat4MultiplyMat4(translateMatrix, mat4MultiplyMat4(scaleMatrix, rotationMatrix));
}