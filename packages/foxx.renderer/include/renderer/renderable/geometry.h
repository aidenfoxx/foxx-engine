#ifndef RENDERER_RENDERABLE_GEOMETRY_H
#define RENDERER_RENDERABLE_GEOMETRY_H

#include <stdio.h>
#include <stdlib.h>
#include <gl/gl3w.h>

#include "common/geometry.h"

typedef struct {
	GLuint vao;
	GLuint vbo[4];
	GLsizei indices;
	struct {
		Vec3 min;
		Vec3 max;
	} aabb;
} RenderableGeometry;

RenderableGeometry *renderableGeometryNew(Geometry);
void renderableGeometryFree(RenderableGeometry*);

#endif