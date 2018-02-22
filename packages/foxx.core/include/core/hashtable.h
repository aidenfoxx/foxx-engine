#ifndef CORE_HASHTABLE_H
#define CORE_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#define HASHTABLE_INITIAL_CAPACITY 512
#define HASHTABLE_RESIZE_MAX .75
#define HASHTABLE_RESIZE_MIN .25

typedef enum {
	HASHTABLE_SUCCESS = 0,
	HASHTABLE_ERROR = INT_MIN
} HashTableStatus;

typedef struct {
	uint8_t active;
	uint32_t key;
	void **data;
} HashEntry;

typedef struct {
	unsigned capacity;
	unsigned length;
	unsigned count;
	HashEntry *entries;
} HashTable;

HashTable *hashTableNew();
void hashTableFree(HashTable*);

void hashTableSet(HashTable*, uint32_t, void*);
void *hashTableGet(HashTable*, uint32_t);
HashTableStatus hashTableRemove(HashTable*, uint32_t);

unsigned hashTableLength(HashTable*);
unsigned hashTableData(HashTable*, void***);

#endif