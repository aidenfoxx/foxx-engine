#include "object.h"

Object *objectNew(Model *model, Texture *diffuse, Texture *specular, Texture *normal)
{
	Object *object = NULL;

	if ((object = malloc(sizeof(Object))) != NULL)
	{
		glGenBuffers(4, object->vbo);

		objectUpdateModel(object, model);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenTextures(1, &object->diffuse);
		glGenTextures(1, &object->specular);
		glGenTextures(1, &object->normal);

		objectUpdateTexture(TEXTURE_DIFFUSE, object, diffuse);
		objectUpdateTexture(TEXTURE_SPECULAR, object, specular);
		objectUpdateTexture(TEXTURE_NORMAL, object, normal);

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
		memcpy(duplicate, object, sizeof(Object));
	}

	return duplicate;
}

void objectFree(Object *object)
{
	if (object)
	{
		glDeleteBuffers(4, object->vbo);
		glDeleteTextures(1, &object->diffuse);
		glDeleteTextures(1, &object->specular);
		glDeleteTextures(1, &object->normal);
		free(object);
	}
}

void objectUpdateModel(Object *object, Model *model)
{
	if (model)
	{
		object->verticesLength = model->verticesLength;
		object->uvsLength = model->uvsLength;
		object->normalsLength = model->normalsLength;
		object->indicesLength = model->indicesLength;

		glBindBuffer(GL_ARRAY_BUFFER, object->vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, object->verticesLength * sizeof(Vec3), (float*)model->vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, object->vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, object->uvsLength * sizeof(Vec2), (float*)model->uvs, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, object->vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, object->normalsLength * sizeof(Vec3), (float*)model->normals, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->vbo[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->indicesLength * sizeof(Vec3), (int*)model->indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void objectUpdateTexture(int textureType, Object *object, Texture *texture)
{
	if (texture)
	{
		switch (textureType)
		{
			case TEXTURE_DIFFUSE:
				glBindTexture(GL_TEXTURE_2D, object->diffuse);
				break;

			case TEXTURE_SPECULAR:
				glBindTexture(GL_TEXTURE_2D, object->specular);
				break;

			case TEXTURE_NORMAL:
				glBindTexture(GL_TEXTURE_2D, object->normal);
				break;
		}

		int dataOffset = 0;

		int mipmapWidth = texture->width;
		int mipmapHeight = texture->height;

		for (int i = 0; i < texture->mipmaps; i++)
		{
			int dataSize = textureCalculateMipmapSize(mipmapWidth, mipmapHeight, texture->blockBytes);
			
			/**
			 * TODO: Check format to decide how to bind.
			 */
			glCompressedTexImage2D(GL_TEXTURE_2D, i, texture->format, mipmapWidth, mipmapHeight, 0, dataSize, &texture->data[dataOffset]);

			dataOffset += dataSize;

			mipmapWidth = floor(mipmapWidth / 2);
			mipmapHeight = floor(mipmapHeight / 2);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
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

void objectUpdateMatrix(Object *object)
{
	Mat4 scaleMatrix = mat4Scale(object->scale);
	Mat4 rotationMatrix  = mat4RotationQuat(eulerConvertQuat(object->rotation));
	Mat4 translateMatrix = mat4Translation(object->translation);

	object->transformMatrix = mat4MultiplyMat4(translateMatrix, mat4MultiplyMat4(scaleMatrix, rotationMatrix));
}