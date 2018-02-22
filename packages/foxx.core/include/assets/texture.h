#ifndef ASSETS_TEXTURE_H
#define ASSETS_TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef enum {
	TEXTURE_RGB,
	TEXTURE_RGBA,
	TEXTURE_RGB_DXT1,
	TEXTURE_RGBA_DXT3,
	TEXTURE_RGBA_DXT5
} TextureFormat;

typedef struct {
	TextureFormat format;
	uint8_t *data;
	unsigned size;
	unsigned width;
	unsigned height;
	unsigned mipmaps;
} Texture;

Texture *textureNew(TextureFormat, uint8_t*, unsigned, unsigned, unsigned);
void textureFree(Texture*);

#endif