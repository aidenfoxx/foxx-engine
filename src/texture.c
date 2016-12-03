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
		texture->data = data;
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
