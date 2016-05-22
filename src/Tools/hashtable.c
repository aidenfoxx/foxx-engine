#include "Tools/hashtable.h"

void hashTableInit(HashTable *table, int size)
{
	table->size = size;
	table->length = 0;
	table->offset = 0;
	table->hashes = calloc(size, sizeof(int));
	table->data = malloc(size * sizeof(int));
}

void hashTableDestroy(HashTable *table)
{
	free(table->hashes);
	free(table->data);
}

int hashTableLength(HashTable *table)
{
	return table->length;
}

int hashTableKey(int value, int key)
{
	if (!key)
	{
		return HASH_MULTIPLIER * HASH_BASE + value;
	}

	return HASH_MULTIPLIER * key + value;
}

int hashTableSet(HashTable *table, int key, int value)
{
	int offset;
	unsigned int hashIndex = (unsigned int) key % table->size;

	/**
	 * TODO: Test that the most un-optimized
	 * hash table still works.
	 */
	while (table->offset < table->size)
	{
		if (table->hashes[hashIndex] == key)
		{
			return 0;
		}
		else if (!table->hashes[hashIndex])
		{
			table->hashes[hashIndex] = key;
			table->data[hashIndex] = value;
			table->length++;
			return 0;
		}

		hashIndex = hashIndex == table->size - 1 ? 0 : hashIndex + 1;
		offset < table->offset ? offset++ : table->offset++;
	}

	return -1;
}

int hashTableGet(HashTable *table, int key)
{
	unsigned int hashIndex = (unsigned int) key % table->size;

	for (int i = 0; i < table->offset + 1; i++)
	{
		if (table->hashes[hashIndex] == key)
		{
			return table->data[hashIndex];
		}
		
		hashIndex = hashIndex == table->size - 1 ? 0 : hashIndex + 1;
	}

	return -1;
}