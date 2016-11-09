#include "Object/texture.h"

int textureInit(Texture *texture, uint8_t *textureData)
{
	texture->data = textureData;
	return 0;
}