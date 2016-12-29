#ifndef TEXTURE_BUFFER_H
#define TEXTURE_BUFFER_H

#include <stdio.h>

#include "context.h"
#include "texture.h"

typedef struct {
	GLuint tbo;
	Texture *texture;
} TextureBuffer;

TextureBuffer *textureBufferNew(Texture*);
void textureBufferFree(TextureBuffer*);

Texture *textureBufferGetTexture(TextureBuffer*);

void textureBufferBind(TextureBuffer*);
void textureBufferUnbind();

#endif