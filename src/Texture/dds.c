#include "Texture/dds.h"

static int textureDDSRead(const char*, uint8_t**);

Texture *textureDDSNew(uint8_t *data)
{
	Texture *texture;

	int magic;

	memcpy(&magic, &data[DDS_MAGIC], sizeof(uint32_t));
	
	if (magic == DDS_MAGIC_VALUE)
	{
		int error;

		GLenum format = 0;
		int width = 0;
		int height = 0;
		int mipmaps = 0;
		int blockBytes = 0;

		memcpy(&format, &data[DDS_FORMAT], sizeof(uint32_t));
		memcpy(&width, &data[DDS_WIDTH], sizeof(uint32_t));
		memcpy(&height, &data[DDS_HEIGHT], sizeof(uint32_t));
		memcpy(&mipmaps, &data[DDS_MIPMAPS], sizeof(uint32_t));

		switch (format)
		{
			case DDS_FORMAT_DXT1:
				format = TEXTURE_FORMAT_DXT1;
				blockBytes = 8;
				break;

			case DDS_FORMAT_DXT3:
				format = TEXTURE_FORMAT_DXT3;
				blockBytes = 16;
				break;

			case DDS_FORMAT_DXT5:
				format = TEXTURE_FORMAT_DXT5;
				blockBytes = 16;
				break;

			default:
				error = -1;
				break;
		}

		uint8_t *textureData;
		int textureSize = textureMipmapsSize(width, height, mipmaps, blockBytes);

		if (!error && (textureData = malloc(textureSize * sizeof(uint8_t))) != NULL)
		{
			memcpy(textureData, &data[DDS_HEADER_SIZE], textureSize * sizeof(uint8_t));
			texture = textureNew(format, textureData, textureSize, width, height, mipmaps, blockBytes);
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

	*textureData = calloc(length, 1);

	if (length != fread(*textureData, 1, length, texture)) 
	{ 
		free(*textureData);
		return 0;
	}

	fclose(texture);

	return length;
}