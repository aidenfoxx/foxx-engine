#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
	uint8_t *data;
} Texture;

int textureInit(Texture*, uint8_t*);

#endif