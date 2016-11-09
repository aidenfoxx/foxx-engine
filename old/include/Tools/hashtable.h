#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

#define HASH_BASE 13
#define HASH_MULTIPLIER 29

typedef struct {
	int size;
	int length;
	int offset;
	int *hashes;
	int *data;
} HashTable;

void hashTableInit(HashTable*, int);
void hashTableDestroy(HashTable*);
int hashTableLength(HashTable*);
int hashTableKey(int, int);
int hashTableSet(HashTable*, int, int);
int hashTableGet(HashTable*, int);

#endif