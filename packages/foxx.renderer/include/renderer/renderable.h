#ifndef RENDERER_RENDERABLE_H
#define RENDERER_RENDERABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "core/math.h"
#include "renderer/typedef.h"
#include "renderer/renderable/geometry.h"
#include "renderer/renderable/material.h"

Renderable *renderableNew(Actor*, RenderableGeometry*, RenderableMaterial*);
void renderableFree(Renderable*);

Vec3 renderableGetTranslation(Renderable*);
void renderableSetTranslation(Renderable*, Vec3);

Vec4 renderableGetRotation(Renderable*);
void renderableSetRotation(Renderable*, Vec4);

Vec3 renderableGetScale(Renderable*);
void renderableSetScale(Renderable*, Vec3);

#endif