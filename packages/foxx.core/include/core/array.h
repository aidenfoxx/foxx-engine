#ifndef CORE_ARRAY_H
#define CORE_ARRAY_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "core/memory.h"

#define ARRAY_INITIAL_CAPACITY 512

typedef enum {
	ARRAY_SUCCESS = 0,
	ARRAY_ERROR = INT_MIN
} ArrayStatus;

typedef struct {
	unsigned length;
	unsigned capacity;
	void **data;
} Array;

Array *arrayNew();
void arrayFree(Array*);

void arrayPush(Array*, void*);
void *arrayPop(Array*);

void arraySet(Array*, unsigned, void*);
void *arrayGet(Array*, unsigned);
ArrayStatus arrayRemove(Array*, unsigned);

unsigned arrayLength(Array*);
unsigned arrayData(Array*, void***);

#endif