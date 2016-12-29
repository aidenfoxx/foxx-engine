#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>

#include "context.h"
#include "object.h"
#include "Model/buffer.h"
#include "Texture/buffer.h"
#include "Renderer/shader.h"
#include "Renderer/camera.h"
#include "Tools/array.h"

#define OBJECT_DYNAMIC 0
#define OBJECT_STATIC 1

typedef struct {
	Camera *camera;
	Array *objects;
	Array *objectsVAO;
	Array *shaders;
} Renderer;

Renderer *rendererNew(Camera*);
void rendererFree(Renderer*);

int rendererAddShader(Renderer*, ShaderProgram*);
int rendererAddObject(Renderer*, Object*);

void rendererRemoveShader(Renderer*, int);
void rendererRemoveObject(Renderer*, int);

void rendererStep(Renderer*);

#endif