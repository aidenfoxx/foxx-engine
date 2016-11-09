#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_INITIAL_CAPACITY 128

typedef struct {
	int length;
	int capacity;
	void **data;
} Array;

void arrayInit(Array*);
int arrayLength(Array*);
void arrayPush(Array*, void*);
void arraySet(Array*, unsigned int, void*);
void *arrayPop(Array*);
void *arrayGet(Array*, unsigned int);
void arrayRemove(Array*, unsigned int);
void arrayDestroy(Array*);
void arrayEmpty(Array*);

#endif