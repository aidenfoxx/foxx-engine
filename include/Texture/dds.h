#ifndef TEXTURE_DDS_H
#define TEXTURE_DDS_H

#include <stdio.h>
#include <stdint.h>

#include "context.h"
#include "texture.h"

#define DDS_HEADER_SIZE 0x80

#define DDS_MAGIC 0x00
#define DDS_FORMAT 0x54
#define DDS_HEIGHT 0x10
#define DDS_WIDTH 0x0C
#define DDS_MIPMAPS 0x1C

#define DDS_MAGIC_VALUE 0x20534444  

#define DDS_FORMAT_DXT1 0x31545844
#define DDS_FORMAT_DXT3 0x33545844
#define DDS_FORMAT_DXT5 0x35545844

Texture *textureDDSNew(uint8_t*);
Texture *textureDDSLoad(const char*);

#endif