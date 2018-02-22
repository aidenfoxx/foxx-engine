#include "common/material.h"

Material materialBasic(Vec3 albedo, float roughness, float metallic)
{
	Material material;

	material.albedo = albedo;
	material.roughness = roughness;
	material.metallic = metallic;

	return material;
}

Material materialFull(Vec3 albedo, 
					  float roughness, 
					  float metallic, 
					  Texture *texture1, 
					  Texture *texture2, 
					  Texture *texture3, 
					  Texture *texture4)
{
	Material material;

	material.albedo = albedo;
	material.roughness = roughness;
	material.metallic = metallic;
	material.texture1 = texture1;
	material.texture2 = texture2;
	material.texture3 = texture3;
	material.texture4 = texture4;

	return material;
}