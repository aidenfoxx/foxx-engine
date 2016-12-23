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

		glGenTextures(1, &texture->tbo);
		glBindTexture(GL_TEXTURE_2D, texture->tbo);

		switch (format)
		{
			case TEXTURE_FORMAT_RGB:
			case TEXTURE_FORMAT_BGR:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, data);
				break;

			case TEXTURE_FORMAT_RGBA:
			case TEXTURE_FORMAT_BGRA:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, data);
				break;

			case TEXTURE_FORMAT_DXT1:
			case TEXTURE_FORMAT_DXT3:
			case TEXTURE_FORMAT_DXT5: ;
				int dataOffset = 0;
				int mipmapWidth = texture->width;
				int mipmapHeight = texture->height;

				for (int i = 0; i < texture->mipmaps; i++)
				{
					int mipmapSize = textureMipmapSize(mipmapWidth, mipmapHeight, texture->blockBytes);
					
					glCompressedTexImage2D(GL_TEXTURE_2D, i, texture->format, mipmapWidth, mipmapHeight, 0, mipmapSize, &data[dataOffset]);
					
					dataOffset += mipmapSize;
					mipmapWidth = floor(mipmapWidth / 2);
					mipmapHeight = floor(mipmapHeight / 2);
				}
				break;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		if ((texture->data = malloc(dataSize * sizeof(uint8_t))))
		{
			memcpy(texture->data, data, dataSize * sizeof(uint8_t));
		}
	}

	return texture;
}

Texture *textureDuplicate(Texture *texture)
{
	return textureNew(texture->format,
					  texture->data,
					  texture->dataSize,
					  texture->width,
					  texture->height,
					  texture->mipmaps,
					  texture->blockBytes);
}

void textureFree(Texture *texture)
{
	if (texture)
	{
		glDeleteTextures(1, &texture->tbo);
		free(texture);
	}
}

void textureBind(int index, Texture *texture)
{
	glActiveTexture(index);
	glBindTexture(GL_TEXTURE_2D, texture->tbo);
}

void textureUnbind()
{
	glActiveTexture(TEXTURE_DIFFUSE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(TEXTURE_SPECULAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(TEXTURE_NORMAL);
	glBindTexture(GL_TEXTURE_2D, 0);
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