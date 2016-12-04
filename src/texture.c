#include "texture.h"

Texture *textureNew(GLenum format, int width, int height, int mipmaps, int blockBytes, uint8_t *data)
{
	Texture *texture = NULL;



	if ((texture = malloc(sizeof(Texture))) != NULL)
	{
		texture->format = format;
		texture->width = width;
		texture->height = height;
		texture->mipmaps = mipmaps;
		texture->blockBytes = blockBytes;
		texture->data = NULL;

		int bufferSize = textureCalculateMipmapsSize(texture->width, texture->height, texture->mipmaps, texture->blockBytes);

		/**
		 * Copy the data to save us managing
		 * it elsewhere.
		 */
		if ((texture->data = malloc(bufferSize * sizeof(uint8_t))))
		{
			memcpy(texture->data, data, bufferSize * sizeof(uint8_t));
		}
	}

	return texture;
}

void textureFree(Texture *texture)
{
	if (texture)
	{
		free(texture->data);
		free(texture);
	}
}

int textureCalculateMipmapsSize(int width, int height, int mipmaps, int blockBytes)
{
	int bufferSize = 0;

	for (int i = 0; i < mipmaps; i++)
	{
		bufferSize += textureCalculateMipmapSize(width, height, blockBytes);

		width = floor(width / 2);
		height = floor(height / 2);
	}

	return bufferSize;
}

int textureCalculateMipmapSize(int width, int height, int blockBytes)
{
	return fmax(4, width) / 4 * fmax(4, height) / 4 * blockBytes;
}