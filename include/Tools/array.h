#ifndef TOOLS_ARRAY_H
#define TOOLS_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_INITIAL_CAPACITY 128

typedef struct {
	int length;
	int capacity;
	void **data;
} Array;

Array *arrayNew();
void arrayFree(Array*);

int arrayLength(Array*);
void arrayPush(Array*, void*);
void arraySet(Array*, unsigned int, void*);
void *arrayPop(Array*);
void *arrayGet(Array*, unsigned int);
void arrayRemove(Array*, unsigned int);
void arrayEmpty(Array*);

#endif