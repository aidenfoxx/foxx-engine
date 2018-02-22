#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

/**
 * Redefine core memory functions.
 */
#define malloc(a) memoryMalloc(a ,__FILE__, __LINE__)
#define calloc(a, b) memoryCalloc(a, b, __FILE__, __LINE__)
#define realloc(a, b) memoryRealloc(a, b, __FILE__, __LINE__)
#define free(a) memoryFree(a, __FILE__, __LINE__)

#define MEMORY_INITIAL_CAPACITY 512
#define MEMORY_RESIZE_MAX .75
#define MEMORY_RESIZE_MIN .25

typedef enum {
	MEMORY_SUCCESS = 0,
	MEMORY_ERROR = INT_MIN
} MemoryError;

typedef struct {
	uintptr_t address;
	size_t size;
	void **buffer;
} MemoryBuffer;

typedef struct {
	unsigned capacity;
	unsigned length;
	unsigned count;
	MemoryBuffer *buffers;
} Memory;

void memoryInit();
void memoryDestroy();

void memorySet(void*, size_t);
MemoryError memoryRemove(void*);

size_t memorySize();
unsigned memoryLength();

/**
 * Core memory functions.
 */
void *memoryMalloc(size_t, const char*, unsigned);
void *memoryCalloc(size_t, size_t, const char*, unsigned);
void *memoryRealloc(void*, size_t, const char*, unsigned);
void memoryFree(void*, const char*, unsigned);

#endif

