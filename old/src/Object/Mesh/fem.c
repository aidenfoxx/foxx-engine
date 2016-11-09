#include "Object/Mesh/fem.h"

static int femToMesh(uint8_t*, Mesh*);

int femLoad(Mesh *mesh, Texture *diffuse, Texture *normal, Texture *specular, const char *path)
{
	struct archive *archive = archive_read_new();
	struct archive_entry *entry;

	archive_read_support_format_tar(archive);
	archive_read_support_filter_compress(archive);
	archive_read_open_filename(archive, path, 10240);

	uint8_t *modelData = NULL;
	uint8_t *diffuseData = NULL;
	uint8_t *normalData = NULL;
	uint8_t *specularData = NULL;

	while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
	{
		int64_t length = archive_entry_size(entry);
		const char *filename = archive_entry_pathname(entry);

		if (mesh != NULL && !strcmp(filename, "model"))
		{
			modelData = malloc((int)length);
			if (archive_read_data(archive, modelData, length) < 1 || femToMesh(modelData, mesh))
				return -1;
		}

		if (diffuse != NULL && !strcmp(filename, "diffuse"))
		{
			diffuseData = malloc((int)length);
			if (archive_read_data(archive, diffuseData, length) < 1 || textureInit(diffuse, diffuseData))
				return -2;
		}

		if (normal != NULL && !strcmp(filename, "normal"))
		{
			normalData = malloc((int)length);
			if (archive_read_data(archive, normalData, length) < 1 || textureInit(normal, normalData))
				return -2;
		}

		if (specular != NULL && !strcmp(filename, "specular"))
		{
			specularData = malloc((int)length);
			if (archive_read_data(archive, specularData, length) < 1 || textureInit(specular, specularData))
				return -2;
		}
	}

	archive_read_close(archive);
	archive_read_free(archive);

	return 0;
}

int femToMesh(uint8_t *data, Mesh *mesh)
{
	printf("Function called.\n");

	mesh->verticesLength = (int)data[0];
	mesh->uvsLength = (int)data[sizeof(int)];
	mesh->normalsLength = (int)data[sizeof(int) * 2];
	mesh->indicesLength = (int)data[sizeof(int) * 3];

	int headerSize = sizeof(int) * 4;
	int verticesSize = mesh->verticesLength * sizeof(Vector3f);
	int uvsSize = mesh->uvsLength * sizeof(Vector2f);
	int normalsSize = mesh->normalsLength * sizeof(Vector3f);
	int indicesSize = mesh->indicesLength * sizeof(Vector3i);

	mesh->vertices = malloc(verticesSize);
	mesh->uvs = malloc(uvsSize);
	mesh->normals = malloc(normalsSize);
	mesh->indices = malloc(indicesSize);

	memcpy(mesh->vertices, &data[headerSize], verticesSize);
	memcpy(mesh->uvs, &data[headerSize + verticesSize], uvsSize);
	memcpy(mesh->normals, &data[headerSize + verticesSize + uvsSize], normalsSize);
	memcpy(mesh->indices, &data[headerSize + verticesSize + uvsSize + normalsSize], indicesSize);

	/**
	 * TODO: Remove.
	 */
	printf("Vertices:\n");

	for (int i = 0; i < mesh->verticesLength; ++i)
		printf("%f %f %f\n", mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z);

	printf("UVs:\n");

	for (int i = 0; i < mesh->uvsLength; ++i)
		printf("%f %f\n", mesh->uvs[i].x, mesh->uvs[i].y);

	printf("Normals:\n");

	for (int i = 0; i < mesh->normalsLength; ++i)
		printf("%f %f %f\n", mesh->normals[i].x, mesh->normals[i].y, mesh->normals[i].z);

	printf("Indices:\n");

	for (int i = 0; i < mesh->indicesLength; ++i)
		printf("%i %i %i\n", mesh->indices[i].x, mesh->indices[i].y, mesh->indices[i].z);

	return 0;
}