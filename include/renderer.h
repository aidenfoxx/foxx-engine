#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>

#include "context.h"
#include "object.h"
#include "Renderer/shader.h"
#include "Renderer/camera.h"
#include "Tools/array.h"

#define OBJECT_DYNAMIC 0
#define OBJECT_STATIC 1

typedef struct {
	Camera *camera;
	GLuint staticVAO;
	Array *dynamicVAOs;
	Array *objectsDynamic;
	Array *objectsStatic;
	Array *shaders;
} Renderer;

Renderer *rendererNew(Camera*);
void rendererFree(Renderer*);

int rendererAddShader(Renderer*, ShaderProgram*);
void rendererRemoveShader(Renderer*, int);

int rendererAddObject(int, Renderer*, Object*);
void rendererRemoveObject(int, Renderer*, int);

void rendererExecute(Renderer*);

#endif