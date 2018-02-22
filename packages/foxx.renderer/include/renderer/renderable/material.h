#ifndef RENDERER_RENDERABLE_MATERIAL_H
#define RENDERER_RENDERABLE_MATERIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <gl/gl3w.h>

#include "common/material.h"

typedef struct {
	GLfloat albedo[3];
	GLfloat roughness;
	GLfloat metallic;
	GLuint tbo[4];
} RenderableMaterial;

RenderableMaterial *renderableMaterialNew(Material);
void renderableMaterialFree(RenderableMaterial*);

#endif