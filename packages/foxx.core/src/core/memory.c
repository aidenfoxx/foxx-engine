#include "core/memory.h"

static Memory *memory = NULL;

static uint32_t memoryHash(uintptr_t);
static void memoryResize(unsigned);

void memoryInit()
{
	assert(memory == NULL);

	memory = (malloc)(sizeof(Memory));

	memory->capacity = MEMORY_INITIAL_CAPACITY;
	memory->length = 0;
	memory->count = 0;
	memory->buffers = (calloc)(MEMORY_INITIAL_CAPACITY, sizeof(MemoryBuffer));
}

void memoryDestroy()
{
	assert(memory != NULL);

	for (unsigned i = 0; i < memory->capacity; i++) {
		if (memory->buffers[i].buffer) {
			(free)(memory->buffers[i].buffer);
		}
	}

	(free)(memory->buffers);
	(free)(memory);

	memory = NULL;
}

void memorySet(void *buffer, size_t size)
{
	assert(memory != NULL);

	unsigned count = 0;
	uintptr_t address = (uintptr_t)buffer;
	unsigned bufferIndex = address % (memory->capacity - 1);

	while (memory->count < memory->capacity) {
		/**
		 * Count defines the longest loop required 
		 * to find a value using a key.
		 */
		if (count == memory->count) {
			memory->count++;
		}

		count++;

		if (!memory->buffers[bufferIndex].address) {
			memory->buffers[bufferIndex].address = address;
			memory->buffers[bufferIndex].size = size;
			memory->buffers[bufferIndex].buffer = buffer;
			memory->length++;

			/**
			 * If the address table is over a certain
			 * percent full, double the table size.
			 */
			if (memory->length > floor(memory->capacity * MEMORY_RESIZE_MAX)) {
				memoryResize(memory->capacity * 2);
			}

			return;
		} else if (memory->buffers[bufferIndex].address == address) {
			memory->buffers[bufferIndex].size = size;
			return;
		}

		bufferIndex = bufferIndex == (memory->capacity - 1) ? 0 : bufferIndex + 1;
	}
}

MemoryError memoryRemove(void *buffer)
{
	assert(memory != NULL);

	uintptr_t address = (uintptr_t)buffer;
	unsigned bufferIndex = address % (memory->capacity - 1);

	for (unsigned i = 0; i < memory->count; i++) {
		if (memory->buffers[bufferIndex].address == address) {
			memory->buffers[bufferIndex].address = 0;
			memory->buffers[bufferIndex].size = 0;
			memory->buffers[bufferIndex].buffer = NULL;
			memory->length--;

			/**
			 * If the table size is sufficiently
			 * lower, resize the table.
			 */
			if (memory->length < floor(memory->capacity * MEMORY_RESIZE_MIN) && memory->capacity > MEMORY_INITIAL_CAPACITY) {
				memoryResize(floor(memory->capacity / 2));
			}

			return MEMORY_SUCCESS;
		}
		
		bufferIndex = bufferIndex == (memory->capacity - 1) ? 0 : bufferIndex + 1;
	}

	return MEMORY_ERROR;
}

size_t memorySize()
{
	assert(memory != NULL);

	size_t size = 0;

	for (unsigned i = 0; i < memory->capacity; i++) {
		if (memory->buffers[i].buffer) {
			size += memory->buffers[i].size;
		}
	}

	return size;
}

unsigned memoryLength()
{
	assert(memory != NULL);

	return memory->length;
}

void *memoryMalloc(size_t size, const char *file, unsigned line)
{
	if (size > 0) {
		void *buffer;

		if ((buffer = (malloc)(size)) != NULL) {
			if (memory != NULL) {
				memorySet(buffer, size);
			}

			return buffer;
		}

		printf("%s:%u: warning: failed to allocate memory buffer\n", file, line);
	}

	return NULL;
}

void *memoryCalloc(size_t size, size_t stride, const char *file, unsigned line)
{
	if (size > 0) {
		void *buffer;

		if ((buffer = (calloc)(size, stride)) != NULL) {
			if (memory != NULL) {
				memorySet(buffer, size * stride);
			}

			return buffer;
		}

		printf("%s:%u: warning: failed to allocate memory buffer\n", file, line);
	}

	return NULL;
}

void *memoryRealloc(void *buffer, size_t size, const char *file, unsigned line)
{
	if (size > 0) {
		void *realloced;

		if ((realloced = (realloc)(buffer, size)) != NULL) {
			if (memory != NULL) {
				memoryRemove(buffer);
				memorySet(realloced, size);
			}

			return realloced;
		}

		printf("%s:%u: warning: failed to reallocate memory buffer\n", file, line);
	}

	/**
	 * Don't need to check if Memory set because
	 * we may want to use default free function.
	 */
	memoryFree(buffer, file, line);

	return NULL;
}

void memoryFree(void *buffer, const char *file, unsigned line)
{
	if (buffer != NULL) {
		if (memory != NULL) {
			if (memoryRemove(buffer) == MEMORY_SUCCESS) {
				(free)(buffer);
				return;
			}
		} else {
			(free)(buffer);
			return;
		}

		printf("%s:%u: warning: failed to free memory buffer. possible double free?\n", file, line);
	}
}

void memoryResize(unsigned size)
{
	unsigned capacity = memory->capacity;
	
	MemoryBuffer *buffers = memory->buffers;
	
	memory->capacity = size;
	memory->length = 0;
	memory->count = 0;
	memory->buffers = (calloc)(size, sizeof(MemoryBuffer));

	for (unsigned i = 0; i < capacity; i++)
	{
		if (buffers[i].address)
		{
			memorySet(buffers[i].buffer, buffers[i].size);
		}
	}

	(free)(buffers);
}