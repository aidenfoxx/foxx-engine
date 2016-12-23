#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "context.h"

#define TEXTURE_FORMAT_RGB 0x1907
#define TEXTURE_FORMAT_BGR 0x80E0
#define TEXTURE_FORMAT_RGBA 0x1908
#define TEXTURE_FORMAT_BGRA 0x80E1

#define TEXTURE_FORMAT_DXT1 0x83F1
#define TEXTURE_FORMAT_DXT3 0x83F2
#define TEXTURE_FORMAT_DXT5 0x83F3

#define TEXTURE_DIFFUSE GL_TEXTURE0
#define TEXTURE_NORMAL GL_TEXTURE1
#define TEXTURE_SPECULAR GL_TEXTURE2

typedef struct {
	GLuint tbo;
	GLenum format;
	uint8_t *data;
	int dataSize;
	int width;
	int height;
	int mipmaps;
	int blockBytes;
} Texture;

Texture *textureNew(GLenum, uint8_t*, int, int, int, int, int);
Texture *textureDuplicate(Texture*);
void textureFree(Texture*);

void textureBind(int, Texture*);
void textureUnbind();

int textureMipmapsSize(int, int, int, int);
int textureMipmapSize(int, int, int);

#endif