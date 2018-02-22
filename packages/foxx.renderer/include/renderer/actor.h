#ifndef SCENE_ACTOR_H
#define SCENE_ACTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "core/math.h"
#include "renderer/typedef.h"
#include "renderer/renderable.h"

Actor *actorNew(Scene*);
void actorFree(Actor*);

Vec3 actorGetTranslation(Actor*);
void actorSetTranslation(Actor*, Vec3);

Vec4 actorGetRotation(Actor*);
void actorSetRotation(Actor*, Vec4);

Vec3 actorGetScale(Actor*);
void actorSetScale(Actor*, Vec3);

#endif