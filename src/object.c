#include "object.h"

void objectInit(Object *object, Mesh *mesh, Texture *diffuse, Texture *specular, Texture *normal)
{
	glGenBuffers(4, object->vbo);

	objectUpdateMesh(object, mesh);
	objectUpdateDiffuse(object, diffuse);
	objectUpdateSpecular(object, specular);
	objectUpdateNormal(object, normal);

	object->scale = vector3f(1.0f, 1.0f, 1.0f);
	object->rotation = vector3f(0.0f, 0.0f, 0.0f);
	object->translation = vector3f(0.0f, 0.0f, 0.0f);

	objectUpdateMatrix(object);
}

void objectDestroy(Object *object)
{
	glDeleteBuffers(4, object->vbo);
}

void objectUpdateMesh(Object *object, Mesh *mesh)
{
	object->mesh = mesh;

	glBindBuffer(GL_ARRAY_BUFFER, object->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, mesh->verticesLength * sizeof(Vector3f), (float*) mesh->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, object->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, mesh->uvsLength * sizeof(Vector2f), (float*) mesh->uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, object->vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, mesh->normalsLength * sizeof(Vector3f), (float*) mesh->normals, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indicesLength * sizeof(Vector3i), (int*) mesh->indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void objectRotate(Object *object, float x, float y, float z)
{
	object->rotation.x += x;
	object->rotation.y += y;
	object->rotation.z += z;

	objectUpdateMatrix(object);
}

void objectTranslate(Object *object, float x, float y, float z)
{
	object->translation.x += x;
	object->translation.y += y;
	object->translation.z += z;

	objectUpdateMatrix(object);
}

void objectScale(Object *object, float x, float y, float z)
{
	object->scale.x *= x;
	object->scale.y *= y;
	object->scale.z *= z;

	objectUpdateMatrix(object);
}

void objectUpdateDiffuse(Object *object, Texture *diffuse)
{
	object->diffuse = diffuse;
}

void objectUpdateSpecular(Object *object, Texture *specular)
{
	object->specular = specular;
}

void objectUpdateNormal(Object *object, Texture *normal)
{
	object->normal = normal;
}

void objectUpdateMatrix(Object *object)
{
	Matrix4 scaleMatrix = matrix4Scale(object->scale);
	Matrix4 rotationMatrix  = matrix4Quat(eulerConvertQuat(object->rotation));
	Matrix4 translateMatrix = matrix4Translate(object->translation);

	object->matrix = matrix4MultiplyMatrix4(translateMatrix, matrix4MultiplyMatrix4(scaleMatrix, rotationMatrix));
}