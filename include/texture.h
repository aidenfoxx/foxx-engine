#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdint.h>

#include "context.h"

typedef struct {
	GLenum format;
	int width;
	int height;
	int mipmaps;
	int blockBytes;
	uint8_t *data;
} Texture;

Texture *textureNew();
void textureFree(Texture*);

#endif