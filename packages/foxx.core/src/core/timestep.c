#include "core/timestep.h"

Timestep *timestepNew(float delta, float deltaCap, float scale)
{
	Timestep *timestep = malloc(sizeof(Timestep));

	timestep->delta = delta > 0.0f ? delta : FLT_TRUE_MIN;
	timestep->deltaCap = deltaCap > 0.0f ? deltaCap : FLT_TRUE_MIN;
	timestep->scale = scale > 0.0f ? scale : FLT_TRUE_MIN;
	timestep->accumulator = 0.0f;
	timestep->previous = clock();

	return timestep;
}

void timestepFree(Timestep *timestep)
{
	assert(timestep != NULL);
	free(timestep);
}

float timestepGetDelta(Timestep *timestep)
{
	assert(timestep != NULL);
	return timestep->delta;
}

void timestepSetDelta(Timestep *timestep, float delta)
{
	assert(timestep != NULL);
	/**
	 * Delta cannot be zero to prevent division error.
	 */
	timestep->delta = delta > 0.0f ? delta : FLT_TRUE_MIN;
}

float timestepGetDeltaCap(Timestep *timestep)
{
	assert(timestep != NULL);
	return timestep->deltaCap;
}

void timestepSetDeltaCap(Timestep *timestep, float deltaCap)
{
	assert(timestep != NULL);
	timestep->deltaCap = deltaCap > 0.0f ? deltaCap : FLT_TRUE_MIN;
}

float timestepGetScale(Timestep *timestep)
{
	assert(timestep != NULL);
	return timestep->scale;
}

void timestepSetScale(Timestep *timestep, float scale)
{
	assert(timestep != NULL);
	/**
	 * Scale cannot be zero to prevent division error.
	 */
	timestep->scale = scale > 0.0f ? scale : FLT_TRUE_MIN;
}

TimestepStatus timestepStatus(Timestep *timestep)
{
	assert(timestep != NULL);
	
	/**
	 * Enough time between frames to execute.
	 */
	if (timestep->accumulator >= 1.0f) {
		timestep->accumulator -= 1.0f;
		return TIMESTEP_EXECUTE;
	}

	clock_t current = clock();

	/**
	 * If not same cycle as previous do
	 * calculations.
	 */
	if (current > timestep->previous) {
		float frameTime = (float)(current - timestep->previous) / CLOCKS_PER_SEC;

		timestep->previous = current;

		/**
		 * If the frame delta exceeded our cap
		 * set only to process at our cap limit.
		 */
		if (frameTime > timestep->deltaCap) {
			frameTime = timestep->deltaCap;
		}
		
		timestep->accumulator += frameTime / (timestep->delta / timestep->scale);
	}

	return TIMESTEP_WAIT;
}