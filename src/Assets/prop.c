#include "Assets/prop.h"

static void propUpdateMatrix(Prop*);

void propInit(Prop *prop, Asset *asset)
{
	prop->asset = asset;
	prop->scale = vector3f(1.0f, 1.0f, 1.0f);
	prop->rotation = vector3f(0.0f, 0.0f, 0.0f);
	prop->translation = vector3f(0.0f, 0.0f, 0.0f);

	propUpdateMatrix(prop);

	/**
	 * Generate buffers.
	 */
	glGenBuffers(4, prop->vbo);

	/**
	 * Bind and fill the buffers.
	 */
	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, asset->indicesCount * sizeof(Vector3f), (float*) asset->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, asset->indicesCount * sizeof(Vector2f), (float*) asset->uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, asset->indicesCount * sizeof(Vector3f), (float*) asset->normals, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prop->vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, asset->indicesLength * sizeof(Vector3i), (unsigned int*) asset->indices, GL_STATIC_DRAW);

	/**
	 * Unbind buffers.
	 */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void propDestroy(Prop *prop)
{
	glDeleteBuffers(4, prop->vbo);
}

void propRotate(Prop *prop, float x, float y, float z)
{
	prop->rotation.x += x;
	prop->rotation.y += y;
	prop->rotation.z += z;

	propUpdateMatrix(prop);
}

void propTranslate(Prop *prop, float x, float y, float z)
{
	prop->translation.x += x;
	prop->translation.y += y;
	prop->translation.z += z;

	propUpdateMatrix(prop);
}

void propScale(Prop *prop, float x, float y, float z)
{
	prop->scale.x *= x;
	prop->scale.y *= y;
	prop->scale.z *= z;

	propUpdateMatrix(prop);
}

void propUpdateMatrix(Prop *prop)
{
	Matrix4 scaleMatrix = matrix4Scale(prop->scale);
	Matrix4 rotationMatrix  = matrix4Quat(eulerConvertQuat(prop->rotation));
	Matrix4 translateMatrix = matrix4Translate(prop->translation);

	prop->matrix = matrix4MultiplyMatrix4(translateMatrix, matrix4MultiplyMatrix4(scaleMatrix, rotationMatrix));
}