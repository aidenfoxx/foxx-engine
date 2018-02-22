#ifndef COMMON_MATERIAL_H
#define COMMON_MATERIAL_H

#include <stdio.h>

#include "core/math.h"
#include "assets/texture.h"

typedef struct {
	Vec3 albedo;
	float roughness;
	float metallic;
	Texture *texture1;
	Texture *texture2;
	Texture *texture3;
	Texture *texture4;
} Material;

Material materialBasic(Vec3, float, float);
Material materialFull(Vec3, float, float, Texture*, Texture*, Texture*, Texture*);

#endif