#ifndef TEXTURE_DDS_H
#define TEXTURE_DDS_H

#include <stdio.h>
#include <stdint.h>

#include "context.h"
#include "texture.h"

#define TEXTURE_DDS_HEADER_SIZE 0x80

#define TEXTURE_DDS_MAGIC 0x00
#define TEXTURE_DDS_FORMAT 0x54
#define TEXTURE_DDS_HEIGHT 0x10
#define TEXTURE_DDS_WIDTH 0x0C
#define TEXTURE_DDS_MIPMAPS 0x1C

#define TEXTURE_DDS_MAGIC_VALUE 0x20534444  

#define TEXTURE_DDS_DXT1_VALUE 0x31545844
#define TEXTURE_DDS_DXT3_VALUE 0x33545844
#define TEXTURE_DDS_DXT5_VALUE 0x35545844

Texture *textureDDSNew(uint8_t*);
Texture *textureDDSLoad(const char*);

#endif