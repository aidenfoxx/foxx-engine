#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>

#include "context.h"
#include "shader.h"
#include "Scene/camera.h"
#include "Scene/actor.h"
#include "Scene/prop.h"
#include "Tools/array.h"

typedef struct {
	GLuint vao;
	Camera *camera;
	ShaderProgram *shader;
	Array *props;
	Array *actors;
} Scene;

void sceneInit(Scene*, Camera*, ShaderProgram*);
void sceneDestroy(Scene*);

void sceneAddProp(Scene*, Prop*);
int sceneAddActor(Scene*, Actor*);
void sceneRemoveActor(Scene*, int);

void sceneRender(Scene*);

#endif