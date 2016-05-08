#ifndef ACTOR_H
#define ACTOR_H

#include <stdio.h>

#include "prop.h"

typedef struct {
	GLuint vao;
	Prop *prop;
} Actor;

void actorInit(Actor*, Asset*);
void actorDestroy(Actor*);
void actorRotate(Actor*, float, float, float);
void actorTranslate(Actor*, float, float, float);
void actorScale(Actor*, float, float, float);

#endif