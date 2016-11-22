#include "Object/fem.h"

Object *objectFemNew(const char *path)
{
	Object *fem = objectNew();

	if (fem)
	{
		uint8_t *modelData = NULL;
		char *diffuseData = NULL;
		char *normalData = NULL;
		char *specularData = NULL;

		struct archive *archive = archive_read_new();
		struct archive_entry *entry;

		archive_read_support_format_tar(archive);
		archive_read_support_filter_compress(archive);
		archive_read_open_filename(archive, path, 10240);

		while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
		{
			int64_t length = archive_entry_size(entry);
			const char *filename = archive_entry_pathname(entry);

			if (!strcmp(filename, "model") && 
				(modelData = malloc((int)length)) != NULL &&
				archive_read_data(archive, modelData, length) == length)
			{
				objectFemUpdateModel(fem, modelData);
			}

			if (!strcmp(filename, "diffuse") &&
				(diffuseData = calloc(sizeof(char), (int)length + 1)) != NULL &&
				archive_read_data(archive, diffuseData, length) == length)
			{
				objectUpdateTexture(TEXTURE_DIFFUSE, fem, diffuseData);
			}

			if (!strcmp(filename, "normal") && 
				(normalData = calloc(sizeof(char), (int)length + 1)) != NULL &&
				archive_read_data(archive, normalData, length) == length)
			{
				objectUpdateTexture(TEXTURE_NORMAL, fem, normalData);
			}

			if (!strcmp(filename, "specular") && 
				(specularData = calloc(sizeof(char), (int)length + 1)) != NULL &&
				archive_read_data(archive, specularData, length) == length)
			{
				objectUpdateTexture(TEXTURE_SPECULAR, fem, specularData);
			}
		}

		archive_read_close(archive);
		archive_read_free(archive);

		free(modelData);
		free(diffuseData);
		free(normalData);
		free(specularData);
	}

	return fem;
}

void objectFemUpdateModel(Object *object, uint8_t *data)
{
	int verticesLength = 0;
	int uvsLength = 0;
	int normalsLength = 0;
	int indicesLength = 0;

	memcpy(&verticesLength, &data[0], sizeof(int));
	memcpy(&uvsLength, &data[sizeof(int)], sizeof(int));
	memcpy(&normalsLength, &data[sizeof(int) * 2], sizeof(int));
	memcpy(&indicesLength, &data[sizeof(int) * 3], sizeof(int));

	int headerSize = sizeof(int) * 4;
	int verticesSize = verticesLength * sizeof(Vec3);
	int uvsSize = uvsLength * sizeof(Vec2);
	int normalsSize = normalsLength * sizeof(Vec3);
	int indicesSize = indicesLength * sizeof(Vec3);

	Vec3 *vertices = malloc(verticesSize);
	Vec2 *uvs = malloc(uvsSize);
	Vec3 *normals = malloc(normalsSize);
	Vec3 *indices = malloc(indicesSize);

	memcpy(vertices, &data[headerSize], verticesSize);
	memcpy(uvs, &data[headerSize + verticesSize], uvsSize);
	memcpy(normals, &data[headerSize + verticesSize + uvsSize], normalsSize);
	memcpy(indices, &data[headerSize + verticesSize + uvsSize + normalsSize], indicesSize);

	objectUpdateModel(object, verticesLength, uvsLength, normalsLength, indicesLength, vertices, uvs, normals, indices);
}