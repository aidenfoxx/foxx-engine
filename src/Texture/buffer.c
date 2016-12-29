#include "Texture/buffer.h"

TextureBuffer *textureBufferNew(Texture *texture)
{
	TextureBuffer *textureBuffer;

	if (texture && (textureBuffer = malloc(sizeof(TextureBuffer))) != NULL)
	{
		textureBuffer->texture = texture;

		glGenTextures(1, &textureBuffer->tbo);

		textureBufferBind(textureBuffer);

		switch (texture->format)
		{
			case TEXTURE_FORMAT_RGB:
			case TEXTURE_FORMAT_BGR:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, texture->data);
				break;

			case TEXTURE_FORMAT_RGBA:
			case TEXTURE_FORMAT_BGRA:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, texture->data);
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
					
					glCompressedTexImage2D(GL_TEXTURE_2D, i, texture->format, mipmapWidth, mipmapHeight, 0, mipmapSize, &texture->data[dataOffset]);
					
					dataOffset += mipmapSize;
					mipmapWidth = floor(mipmapWidth / 2);
					mipmapHeight = floor(mipmapHeight / 2);
				}
				break;
		}

		textureBufferUnbind();
	}

	return textureBuffer;
}

void textureBufferFree(TextureBuffer *textureBuffer)
{
	if (textureBuffer)
	{
		glDeleteTextures(1, &textureBuffer->tbo);
		free(textureBuffer);
	}
}

Texture *textureBufferGetTexture(TextureBuffer *textureBuffer)
{
	return textureBuffer->texture;
}

void textureBufferBind(TextureBuffer *textureBuffer)
{
	glBindTexture(GL_TEXTURE_2D, textureBuffer->tbo);
}

void textureBufferUnbind()
{
	glActiveTexture(TEXTURE_DIFFUSE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(TEXTURE_SPECULAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(TEXTURE_NORMAL);
	glBindTexture(GL_TEXTURE_2D, 0);
}