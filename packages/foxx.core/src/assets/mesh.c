#include "assets/mesh.h"

Mesh *meshNew(Vec3 *vertices, 
			  Vec2 *uvs,
			  Vec3 *normals,
			  unsigned *indices,
			  unsigned verticesLength,
			  unsigned uvsLength,
			  unsigned normalsLength,
			  unsigned indicesLength)
{
	Mesh *mesh = malloc(sizeof(Mesh));

	mesh->vertices.data = malloc(verticesLength * sizeof(Vec3));
	mesh->uvs.data = malloc(uvsLength * sizeof(Vec2));
	mesh->normals.data = malloc(normalsLength * sizeof(Vec3));
	mesh->indices.data = malloc(indicesLength * sizeof(unsigned));

	memcpy(mesh->vertices.data, vertices, verticesLength * sizeof(Vec3));
	memcpy(mesh->uvs.data, uvs, uvsLength * sizeof(Vec2));
	memcpy(mesh->normals.data, normals, normalsLength * sizeof(Vec3));
	memcpy(mesh->indices.data, indices, indicesLength * sizeof(unsigned));

	mesh->vertices.length = verticesLength;
	mesh->uvs.length = uvsLength;
	mesh->normals.length = normalsLength;
	mesh->indices.length = indicesLength;

	return mesh;
}

void meshFree(Mesh *mesh)
{
	assert(mesh != NULL);

	free(mesh->vertices.data);
	free(mesh->uvs.data);
	free(mesh->normals.data);
	free(mesh->indices.data);
	free(mesh);
}