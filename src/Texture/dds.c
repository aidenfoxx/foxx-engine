#include "Texture/dds.h"

Texture *textureDDSNew(uint8_t *data)
{
	int magic;

	GLenum format = 0;
	int width = 0;
	int height = 0;
	int mipmaps = 0;
	int blockBytes = 0;
	uint8_t *textureData = NULL;

	memcpy(&magic, &data[TEXTURE_DDS_MAGIC], sizeof(uint32_t));
	
	if (magic == TEXTURE_DDS_MAGIC_VALUE)
	{
		int typeError;
		int mipmapWidth = 0;
		int mipmapHeight = 0;
		int bufferSize = 0;

		memcpy(&format, &data[TEXTURE_DDS_FORMAT], sizeof(uint32_t));
		memcpy(&width, &data[TEXTURE_DDS_WIDTH], sizeof(uint32_t));
		memcpy(&height, &data[TEXTURE_DDS_HEIGHT], sizeof(uint32_t));
		memcpy(&mipmaps, &data[TEXTURE_DDS_MIPMAPS], sizeof(uint32_t));

		mipmapWidth = width;
		mipmapHeight = height;

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

		for (int i; i < mipmaps; i++)
		{
			bufferSize += fmax(4, mipmapWidth) / 4 * fmax(4, mipmapHeight) / 4 * blockBytes;

			mipmapWidth = floor(mipmapWidth / 2);
			mipmapHeight = floor(mipmapHeight / 2);
		}

		if (!typeError && (textureData = malloc(bufferSize * sizeof(uint8_t))))
		{
			memcpy(textureData, &data[TEXTURE_DDS_HEADER_SIZE], bufferSize);
		}
	}

	return textureNew(format, width, height, mipmaps, blockBytes, textureData);
}