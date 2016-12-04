#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

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

int textureCalculateMipmapsSize(int, int, int, int);
int textureCalculateMipmapSize(int, int, int);

#endif