#include "core/array.h"

Array *arrayNew()
{
	Array *array = malloc(sizeof(Array));

	array->capacity = ARRAY_INITIAL_CAPACITY;
	array->length = 0;
	array->data = malloc(ARRAY_INITIAL_CAPACITY * sizeof(void*));

	return array;
}

void arrayFree(Array *array)
{
	assert(array != NULL);
	free(array->data);
	free(array);
}

void arrayPush(Array *array, void *data)
{
	assert(array != NULL);

	/**
	 * If the array is at capacity, double
	 * the capacity.
	 */
	if (array->length == array->capacity) {
		array->capacity = array->capacity * 2;
		array->data = realloc(array->data, array->capacity * sizeof(void*));
	}

	array->data[array->length] = data; 
	array->length++;
}

void *arrayPop(Array *array)
{
	assert(array != NULL);

	if (array->length > 0) {
		void *data = array->data[array->length - 1];
		arrayRemove(array, array->length - 1);
		return data;
	}

	return NULL;
}

void arraySet(Array *array, unsigned index, void *data)
{
	assert(array != NULL);

	unsigned length = index + 1;

	/**
	 * If our new position is >= the capacity,
	 * double the capacity.
	 */
	if (length >= array->capacity) {
		while (length >= array->capacity) {
			array->capacity = array->capacity * 2;
		}

		array->data = realloc(array->data, array->capacity * sizeof(void*));
	}

	/**
	 * If the index we're setting increases
	 * the length of the array, null set the
	 * data between the current values and our
	 * new index.
	 */
	if (length > array->length) {
		unsigned padding = index - array->length;

		if (padding > 0) {
			memset(&array->data[array->length], 0, padding * sizeof(void*));
		}

		array->length = length;
	}

	array->data[index] = data;
}

void *arrayGet(Array *array, unsigned index)
{
	assert(array != NULL);

	if (index < array->length) {
		return array->data[index];
	}

	return NULL;
}

ArrayStatus arrayRemove(Array *array, unsigned index)
{
	assert(array != NULL);

	if (index < array->length && array->data[index] != NULL)
	{
		array->data[index] = NULL;

		/**
		 * If the trailing array data is
		 * null remove all null values.
		 */
		while (array->data[array->length - 1] == NULL)
		{
			/**
			 * If array is half the capacity
			 * of the data, resize.
			 */
			if (array->length == floor(array->capacity / 2) && array->capacity > ARRAY_INITIAL_CAPACITY)
			{
				array->capacity = floor(array->capacity / 2);
				array->data = realloc(array->data, array->capacity * sizeof(void*)); 
			}

			array->length--;
		}

		return ARRAY_SUCCESS;
	}

	return ARRAY_ERROR;
}

unsigned arrayLength(Array *array)
{
	assert(array != NULL);

	return array->length;
}

unsigned arrayData(Array *array, void ***data)
{
	assert(array != NULL);
	
	if (array->length)
	{
		*data = malloc(array->length * sizeof(void*));

		for (unsigned i = 0; i < array->length; i++)
		{
			(*data)[i] = arrayGet(array, i);
		}
	}

	return array->length;
}