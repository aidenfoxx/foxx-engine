#ifndef CORE_TIMESTEP_H
#define CORE_TIMESTEP_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <assert.h>

typedef enum {
	TIMESTEP_EXECUTE = 0,
	TIMESTEP_WAIT = INT_MIN
} TimestepStatus;

typedef struct {
	float delta;
	float deltaCap;
	float scale;
	float accumulator;
	clock_t previous;
} Timestep;

Timestep *timestepNew(float, float, float);
void timestepFree(Timestep *timestep);

float timestepGetDelta(Timestep *timestep);
void timestepSetDelta(Timestep *timestep, float);

float timestepGetDeltaCap(Timestep*);
void timestepSetDeltaCap(Timestep*, float);

float timestepGetScale(Timestep*);
void timestepSetScale(Timestep*, float);

TimestepStatus timestepStatus(Timestep*);

#endif