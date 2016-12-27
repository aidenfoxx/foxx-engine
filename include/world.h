#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>
#include <ode/ode.h>

#include "object.h"
#include "Tools/array.h"
#include "Tools/glmath.h"

#define WORLD_GRAVITY_X 0.0f
#define WORLD_GRAVITY_Y -9.81f
#define WORLD_GRAVITY_Z 0.0f
#define WORLD_SURFACE_LAYER 0.001
#define WORLD_ERROR_CORRECTION 0.2f
#define WORLD_CONSTRAINT_FORCE 1e-5

typedef struct {
	dWorldID world;
	dSpaceID space;
	dJointGroupID contactGroup; 
	Array *bodies;
	Array *joints;
} World;

World *worldNew();
void worldFree(World*);

void worldSetGravity(World*, Vec3);

int worldAddObject(World*, Object*);
void worldRemoveObject(World*, int);

void worldStep(World*, float);

#endif