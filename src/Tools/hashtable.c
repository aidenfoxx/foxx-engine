#include "Tools/hashtable.h"

HashTable *hashTableNew(unsigned int size)
{
	HashTable *table = NULL;

	if ((table = malloc(sizeof(HashTable))) != NULL)
	{
		table->size = size;
		table->length = 0;
		table->count = 0;
		table->hashes = calloc(size, sizeof(int));
		table->data = malloc(size * sizeof(int));
	}

	return table;
}

void hashTableFree(HashTable *table)
{
	if (table != NULL)
	{
		free(table->hashes);
		free(table->data);
		free(table);
	}
}

int hashTableLength(HashTable *table)
{
	return table->length;
}

int hashTableKey(unsigned int key, unsigned int value)
{
	if (key == 0)
	{
		return HASH_MULTIPLIER * HASH_BASE + value;
	}
	return HASH_MULTIPLIER * key + value;
}

int hashTableSet(HashTable *table, unsigned int key, unsigned int value)
{
	int count = 0;
	unsigned int hashIndex = key % (table->size - 1);

	/**
	 * Don't minus 1 to make it equivelent to <=
	 */
	while (table->count < table->size)
	{
		if (count == table->count)
		{
			table->count++;
		}

		count++;

		/**
		 * If value already exists at that
		 * index then do nothing.
		 */
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

		hashIndex = hashIndex == (table->size - 1) ? 0 : hashIndex + 1;
	}

	return -1;
}

int hashTableGet(HashTable *table, unsigned int key)
{
	unsigned int hashIndex = (unsigned int)key % (table->size - 1);

	for (int i = 0; i < table->count; i++)
	{
		if (table->hashes[hashIndex] == key)
		{
			return table->data[hashIndex];
		}
		
		hashIndex = hashIndex == (table->size - 1) ? 0 : hashIndex + 1;
	}

	return -1;
}