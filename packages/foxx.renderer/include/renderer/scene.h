#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gl/gl3w.h>

#include "core/math.h"
#include "renderer/typedef.h"
#include "renderer/camera.h"
#include "renderer/shader.h"
#include "renderer/actor.h"

Scene *sceneNew(Camera*, Shader*);
void sceneFree(Scene*);

void sceneStep(Scene*);

#endif