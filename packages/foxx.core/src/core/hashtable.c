#include "core/hashtable.h"

static void hashTableResize(HashTable*, unsigned);

HashTable *hashTableNew() {
	HashTable *table = malloc(sizeof(HashTable));

	table->capacity = HASHTABLE_INITIAL_CAPACITY;
	table->length = 0;
	table->count = 0;
	table->entries = calloc(HASHTABLE_INITIAL_CAPACITY, sizeof(HashEntry));

	return table;
}

void hashTableFree(HashTable *table) {
	assert(table != NULL);
	free(table->entries);
	free(table);
}

void hashTableSet(HashTable *table, uint32_t key, void *data) {
	assert(table != NULL);

	unsigned count = 0;
	unsigned hashIndex = key % (table->capacity - 1);

	while (table->count < table->capacity) {
		/**
		 * Count defines the longest loop required 
		 * to find a value using a key.
		 */
		if (count == table->count) {
			table->count++;
		}

		count++;

		if (!table->entries[hashIndex].active && !table->entries[hashIndex].key) {
			table->entries[hashIndex].active = 1;
			table->entries[hashIndex].key = key;
			table->entries[hashIndex].data = data;
			
			table->length++;

			/**
			 * If the hash table is over a certain
			 * percent full, double the table size.
			 */
			if (table->length > floor(table->capacity * HASHTABLE_RESIZE_MAX)) {
				hashTableResize(table, table->capacity * 2);
			}

			return;
		} else if (table->entries[hashIndex].key == key) {
			table->entries[hashIndex].data = data;
			return;
		}

		hashIndex = hashIndex == (table->capacity - 1) ? 0 : hashIndex + 1;
	}
}

void *hashTableGet(HashTable *table, uint32_t key)
{
	assert(table != NULL);

	unsigned hashIndex = key % (table->capacity - 1);

	for (unsigned i = 0; i < table->count; i++) {
		/**
		 * If there is a key, or the value is
		 * intentionally zero, do check.
		 */
		if (table->entries[hashIndex].active && table->entries[hashIndex].key == key) {
			return table->entries[hashIndex].data;
		}
		
		hashIndex = hashIndex == (table->capacity - 1) ? 0 : hashIndex + 1;
	}

	return NULL;
}

HashTableStatus hashTableRemove(HashTable *table, uint32_t key)
{
	assert(table != NULL);

	unsigned hashIndex = key % (table->capacity - 1);

	for (unsigned i = 0; i < table->count; i++) {
		if (table->entries[hashIndex].active && table->entries[hashIndex].key == key) {
			table->entries[hashIndex].active = 0;
			table->entries[hashIndex].key = 0;
			table->entries[hashIndex].data = NULL;

			table->length--;

			/**
			 * If the table size is sufficiently
			 * lower, resize the table.
			 */
			if (table->length < floor(table->capacity * HASHTABLE_RESIZE_MIN) && table->capacity > HASHTABLE_INITIAL_CAPACITY) {
				hashTableResize(table, floor(table->capacity / 2));
			}

			return HASHTABLE_SUCCESS;
		}
		
		hashIndex = hashIndex == (table->capacity - 1) ? 0 : hashIndex + 1;
	}

	return HASHTABLE_ERROR;
}

unsigned hashTableLength(HashTable *table)
{
	assert(table != NULL);

	return table->length;
}

unsigned hashTableData(HashTable *table, void ***data)
{
	assert(table != NULL);

	if (table->length > 0) {
		unsigned index = 0;
		void **temp = malloc(table->length * sizeof(void*));

		for (unsigned i = 0; i < table->capacity; i++) {
			/**
			 * We have keys equal to the number
			 * of elements in the table.
			 */
			if (index == table->length) {
				break;
			}

			if (table->entries[i].active) {
				temp[index] = table->entries[i].data;
				index++;
			}
		}

		if (index == table->length) {
			*data = temp;
			return table->length;
		}

		free(temp);
	}

	return 0;
}

void hashTableResize(HashTable *table, unsigned size)
{
	unsigned capacity = table->capacity;
	
	HashEntry *entries = table->entries;
	
	table->capacity = size;
	table->length = 0;
	table->count = 0;
	table->entries = calloc(size, sizeof(HashEntry));

	for (unsigned i = 0; i < capacity; i++) {
		if (entries[i].active) {
			hashTableSet(table, entries[i].key, entries[i].data);
		}
	}

	free(entries);
}