#ifndef ASSETS_MESH_H
#define ASSETS_MESH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "core/math.h"

typedef struct {
	struct {
		Vec3 *data;
		unsigned length;
	} vertices;
	struct {
		Vec2 *data;
		unsigned length;
	} uvs;
	struct {
		Vec3 *data;
		unsigned length;
	} normals;
	struct {
		unsigned *data;
		unsigned length;
	} indices;
} Mesh;

Mesh *meshNew(Vec3*, Vec2*, Vec3*, unsigned*, unsigned, unsigned, unsigned, unsigned);
void meshFree(Mesh*);

#endif