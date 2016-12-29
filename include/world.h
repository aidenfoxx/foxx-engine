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

#define WORLD_AUTO_DISABLE 0
#define WORLD_SURFACE_LAYER 0.001f
#define WORLD_ERP 0.2f
#define WORLD_CFM 1e-5

#define WORLD_MAX_CONTACTS 8

typedef struct {
	dWorldID world;
	dSpaceID space;
	dJointGroupID contactGroup; 
	Array *bodies;
	Array *joints;
} World;

World *worldNew();
void worldFree(World*);

int worldAddObject(World*, Object*);
void worldRemoveObject(World*, int);

void worldSetAutoDisable(World*, int);
void worldSetGravity(World*, Vec3);
void worldSetSurfaceLayer(World*, float);
void worldSetERP(World*, float);
void worldSetCFM(World*, float);

int worldGetAutoDisable(World*);
Vec3 worldGetGravity(World*);
float worldGetSurfaceLayer(World*);
float worldGetERP(World*);
float worldGetCFM(World*);

void worldStep(World*, float);

#endif