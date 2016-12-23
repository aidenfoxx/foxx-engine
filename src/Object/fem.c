#include "Object/fem.h"

Model *objectFemModel(uint8_t*);

Object *objectFemLoad(const char *path)
{
	Model *model = NULL;
	Texture *diffuse = NULL;
	Texture *specular = NULL;
	Texture *normal = NULL;

	uint8_t *dataBuffer = NULL;

	struct archive *archive = archive_read_new();
	struct archive_entry *entry;

	archive_read_support_format_tar(archive);
	archive_read_support_filter_compress(archive);
	archive_read_open_filename(archive, path, 10240);

	while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
	{
		int64_t length = archive_entry_size(entry);
		const char *filename = archive_entry_pathname(entry);

		if ((dataBuffer = malloc((int)length)) != NULL)
		{
			if (!strcmp(filename, "model") && 
				archive_read_data(archive, dataBuffer, length) == length)
			{
				model = objectFemModel(dataBuffer);
			}

			if (!strcmp(filename, "diffuse") &&
				archive_read_data(archive, dataBuffer, length) == length)
			{
				diffuse = textureDDSNew(dataBuffer);
			}

			if (!strcmp(filename, "specular") && 
				archive_read_data(archive, dataBuffer, length) == length)
			{
				specular = textureDDSNew(dataBuffer);
			}

			if (!strcmp(filename, "normal") && 
				archive_read_data(archive, dataBuffer, length) == length)
			{
				normal = textureDDSNew(dataBuffer);
			}

			free(dataBuffer);
			dataBuffer = NULL;
		}
	}

	archive_read_close(archive);
	archive_read_free(archive);

	return objectNew(model, diffuse, specular, normal);
}

void objectFemFree(Object *object)
{
	modelFree(objectGetModel(object));
	textureFree(objectGetTexture(TEXTURE_DIFFUSE, object));
	textureFree(objectGetTexture(TEXTURE_SPECULAR, object));
	textureFree(objectGetTexture(TEXTURE_NORMAL, object));
	objectFree(object);
}

Model *objectFemModel(uint8_t *data)
{
	/**
	 * Get the size of data.
	 */
	int verticesLength = 0;
	int uvsLength = 0;
	int normalsLength = 0;
	int indicesLength = 0;

	memcpy(&verticesLength, &data[0], sizeof(int));
	memcpy(&uvsLength, &data[sizeof(int)], sizeof(int));
	memcpy(&normalsLength, &data[sizeof(int) * 2], sizeof(int));
	memcpy(&indicesLength, &data[sizeof(int) * 3], sizeof(int));

	/**
	 * Get the data.
	 */
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

	Model *model = modelNew(vertices, uvs, normals, indices, verticesLength, uvsLength, normalsLength, indicesLength);

	free(vertices);
	free(uvs);
	free(normals);
	free(indices);

	return model;
}