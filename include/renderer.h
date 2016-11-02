#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>

#include "context.h"
#include "object.h"
#include "Renderer/shader.h"
#include "Renderer/camera.h"
#include "Tools/array.h"

typedef struct {
	Camera *camera;
	Array *lights;
	Array *shaders;
	GLuint staticVAO;
	Array *objectsVAO;
	Array *objectsDynamic;
	Array *objectsStatic;
} Renderer;

int rendererInit(Renderer*, Camera*);
void rendererDestroy(Renderer*);
int rendererAddShader(Renderer*, ShaderProgram*);
void rendererRemoveShader(Renderer*, int);
int rendererAddObject(Renderer*, Object*, int);
void rendererRemoveObject(Renderer*, int, int);
void rendererExecute(Renderer*);

#endif