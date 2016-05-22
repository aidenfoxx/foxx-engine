#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>

#include "context.h"
#include "shader.h"

#include "Assets/camera.h"
#include "Assets/actor.h"
#include "Assets/prop.h"
#include "Tools/array.h"

typedef struct {
	GLuint vao;
	Camera *camera;
	Array *shaders;
	Array *props;
	Array *actors;
	Array *lights;
} Scene;

int sceneInit(Scene*, Camera*);
void sceneDestroy(Scene*);
int sceneAddShader(Scene*, ShaderProgram*);
void sceneRemoveShader(Scene*, int);
void sceneAddProp(Scene*, Prop*);
int sceneAddActor(Scene*, Actor*);
void sceneRemoveActor(Scene*, int);
void sceneRender(Scene*);

#endif