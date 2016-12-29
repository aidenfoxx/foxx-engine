#include "texture.h"

Texture *textureNew(GLenum format, uint8_t *data, int dataSize, int width, int height, int mipmaps, int blockBytes)
{
	Texture *texture;

	if ((texture = malloc(sizeof(Texture))) != NULL)
	{
		texture->format = format;
		texture->width = width;
		texture->height = height;
		texture->mipmaps = mipmaps;
		texture->blockBytes = blockBytes;
		texture->data = NULL;
		texture->dataSize = dataSize;

		if ((texture->data = malloc(dataSize * sizeof(uint8_t))))
		{
			memcpy(texture->data, data, dataSize * sizeof(uint8_t));
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

int textureMipmapsSize(int width, int height, int mipmaps, int blockBytes)
{
	int bufferSize = 0;

	for (int i = 0; i < mipmaps; i++)
	{
		bufferSize += textureMipmapSize(width, height, blockBytes);

		width = floor(width / 2);
		height = floor(height / 2);
	}

	return bufferSize;
}

int textureMipmapSize(int width, int height, int blockBytes)
{
	return fmax(4, width) / 4 * fmax(4, height) / 4 * blockBytes;
}