#include "Texture/dds.h"

static int textureDDSRead(const char*, uint8_t**);

Texture *textureDDSNew(uint8_t *data)
{
	Texture *texture = NULL;

	int magic;

	memcpy(&magic, &data[TEXTURE_DDS_MAGIC], sizeof(uint32_t));
	
	if (magic == TEXTURE_DDS_MAGIC_VALUE)
	{
		int typeError;

		GLenum format = 0;
		int width = 0;
		int height = 0;
		int mipmaps = 0;
		int blockBytes = 0;

		memcpy(&format, &data[TEXTURE_DDS_FORMAT], sizeof(uint32_t));
		memcpy(&width, &data[TEXTURE_DDS_WIDTH], sizeof(uint32_t));
		memcpy(&height, &data[TEXTURE_DDS_HEIGHT], sizeof(uint32_t));
		memcpy(&mipmaps, &data[TEXTURE_DDS_MIPMAPS], sizeof(uint32_t));

		switch (format)
		{
			case TEXTURE_DDS_DXT1_VALUE:
				format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				blockBytes = 8;
				break;

			case TEXTURE_DDS_DXT3_VALUE:
				format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				blockBytes = 16;
				break;

			case TEXTURE_DDS_DXT5_VALUE:
				format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				blockBytes = 16;
				break;

			default:
				typeError = 1;
				break;
		}

		uint8_t *textureData;

		int bufferSize = textureCalculateMipmapsSize(width, height, mipmaps, blockBytes);

		if (!typeError && (textureData = malloc(bufferSize * sizeof(uint8_t))) != NULL)
		{
			memcpy(textureData, &data[TEXTURE_DDS_HEADER_SIZE], bufferSize * sizeof(uint8_t));
			texture = textureNew(format, width, height, mipmaps, blockBytes, textureData);
			free(textureData);
		}
	}

	return texture;
}

Texture *textureDDSLoad(const char *path)
{
	Texture *texture = NULL;
	uint8_t *textureData = NULL;

	if (textureDDSRead(path, &textureData) > 0)
	{
		texture = textureDDSNew(textureData);
	}

	free(textureData);

	return texture;
}

int textureDDSRead(const char *texturePath, uint8_t **textureData)
{
	FILE *texture = fopen(texturePath, "rb");

	if (!texture)
	{
		return 0;
	}

	fseek(texture, 0, SEEK_END);
	long length = ftell(texture);
	fseek(texture, 0, SEEK_SET);

	*textureData = calloc(length + 1, 1);

	if (length != fread(*textureData, 1, length, texture)) 
	{ 
		free(*textureData);
		return 0;
	}

	fclose(texture);

	return length;
}