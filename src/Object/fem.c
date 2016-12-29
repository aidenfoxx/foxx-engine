#include "Object/fem.h"

Model *objectFemModel(uint8_t*);

Object *objectFemLoad(const char *path)
{
	ModelBuffer *modelBuffer = NULL;
	TextureBuffer *diffuseBuffer = NULL;
	TextureBuffer *specularBuffer = NULL;
	TextureBuffer *normalBuffer = NULL;

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
				modelBuffer = modelBufferNew(objectFemModel(dataBuffer));
			}

			if (!strcmp(filename, "diffuse") &&
				archive_read_data(archive, dataBuffer, length) == length)
			{
				diffuseBuffer = textureBufferNew(textureDDSNew(dataBuffer));
			}

			if (!strcmp(filename, "specular") && 
				archive_read_data(archive, dataBuffer, length) == length)
			{
				specularBuffer = textureBufferNew(textureDDSNew(dataBuffer));
			}

			if (!strcmp(filename, "normal") && 
				archive_read_data(archive, dataBuffer, length) == length)
			{
				normalBuffer = textureBufferNew(textureDDSNew(dataBuffer));
			}

			free(dataBuffer);
			dataBuffer = NULL;
		}
	}

	archive_read_close(archive);
	archive_read_free(archive);

	free(dataBuffer);

	return objectNew(modelBuffer, diffuseBuffer, specularBuffer, normalBuffer);
}

void objectFemFree(Object *object)
{
	ModelBuffer *modelBuffer;
	TextureBuffer *diffuseBuffer;
	TextureBuffer *specularBuffer;
	TextureBuffer *normalBuffer;

	if (modelBuffer = objectGetModelBuffer(object))
	{
		modelFree(modelBufferGetModel(modelBuffer));
		modelBufferFree(modelBuffer);
	}

	if (diffuseBuffer = objectGetTextureBuffer(object, TEXTURE_DIFFUSE))
	{
		textureFree(textureBufferGetTexture(diffuseBuffer));
		textureBufferFree(diffuseBuffer);
	}

	if (specularBuffer = objectGetTextureBuffer(object, TEXTURE_SPECULAR))
	{
		textureFree(textureBufferGetTexture(specularBuffer));
		textureBufferFree(specularBuffer);
	}

	if (normalBuffer = objectGetTextureBuffer(object, TEXTURE_NORMAL))
	{
		textureFree(textureBufferGetTexture(normalBuffer));
		textureBufferFree(normalBuffer);
	}

	objectFree(object);
}

Model *objectFemModel(uint8_t *data)
{
	Model *model;

	/**
	 * Get the size of data.
	 */
	int verticesLength = 0;
	int uvsLength = 0;
	int normalsLength = 0;
	int indicesLength = 0;

	/**
	 * TODO: Convert to uints
	 */
	memcpy(&verticesLength, &data[0], sizeof(int));
	memcpy(&uvsLength, &data[sizeof(int)], sizeof(int));
	memcpy(&normalsLength, &data[sizeof(int) * 2], sizeof(int));
	memcpy(&indicesLength, &data[sizeof(int) * 3], sizeof(int));

	/**
	 * Get the data.
	 */
	Vec3 *vertices = NULL;
	Vec2 *uvs = NULL;
	Vec3 *normals = NULL;
	int *indices = NULL;

	int headerSize = sizeof(int) * 4;
	int verticesSize = verticesLength * sizeof(Vec3);
	int uvsSize = uvsLength * sizeof(Vec2);
	int normalsSize = normalsLength * sizeof(Vec3);
	int indicesSize = indicesLength * sizeof(int);

	if ((vertices = malloc(verticesSize)) != NULL &&
		(uvs = malloc(uvsSize)) != NULL &&
		(normals = malloc(normalsSize)) != NULL &&
		(indices = malloc(indicesSize)) != NULL)
	{
		memcpy(vertices, &data[headerSize], verticesSize);
		memcpy(uvs, &data[headerSize + verticesSize], uvsSize);
		memcpy(normals, &data[headerSize + verticesSize + uvsSize], normalsSize);
		memcpy(indices, &data[headerSize + verticesSize + uvsSize + normalsSize], indicesSize);

		model = modelNew(vertices, uvs, normals, indices, verticesLength, uvsLength, normalsLength, indicesLength);
	}

	free(vertices);
	free(uvs);
	free(normals);
	free(indices);

	return model;
}