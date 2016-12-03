#ifndef TOOLS_HASHTABLE_H
#define TOOLS_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

#define HASH_BASE 13
#define HASH_MULTIPLIER 29

typedef struct {
	int size;
	int length;
	int count;
	unsigned int *hashes;
	unsigned int *data;
} HashTable;

HashTable *hashTableNew(int);
void hashTableFree(HashTable*);
int hashTableLength(HashTable*);
int hashTableKey(unsigned int, int);
int hashTableSet(HashTable*, unsigned int, int);
int hashTableGet(HashTable*, unsigned int);

#endif