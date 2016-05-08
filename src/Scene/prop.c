#include "Scene/prop.h"

static void propUpdateMatrix(Prop*);

void propInit(Prop *prop, Asset *asset)
{
	prop->asset = asset;
	prop->scale = vec3New(1.0f, 1.0f, 1.0f);
	prop->rotation = vec3New(0.0f, 0.0f, 0.0f);
	prop->translation = vec3New(0.0f, 0.0f, 0.0f);

	propUpdateMatrix(prop);

	/**
	 * Generate buffers.
	 */
	glGenBuffers(4, prop->vbo);

	/**
	 * Bind and fill the buffers.
	 */
    glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * asset->vertexLength, asset->vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * asset->uvLength, asset->uvData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * asset->normalLength, asset->normalData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prop->vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * asset->indexLength, asset->indexData, GL_STATIC_DRAW);

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
	Matrix scaleMatrix = matrixScale(prop->scale);
	Matrix rotationMatrix  = matrixRotateQuat(eulerConvertQuat(prop->rotation));
	Matrix translateMatrix = matrixTranslate(prop->translation);

	prop->matrix = matrixMultiplyMatrix(translateMatrix, matrixMultiplyMatrix(scaleMatrix, rotationMatrix));
}