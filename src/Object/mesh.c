#include "Object/mesh.h"

void meshInit(Mesh *mesh)
{
	mesh->verticesLength = 0;
	mesh->uvsLength = 0;
	mesh->normalsLength = 0;
	mesh->indicesLength = 0;

	mesh->vertices = NULL;
	mesh->uvs = NULL;
	mesh->normals = NULL;
	mesh->indices = NULL;
}

void meshDestroy(Mesh *mesh)
{
	free(mesh->vertices);
	free(mesh->uvs);
	free(mesh->normals);
	free(mesh->indices);
}