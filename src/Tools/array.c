#include "Tools/array.h"

void arrayInit(Array *array)
{
	array->length = 0;
	array->capacity = ARRAY_INITIAL_CAPACITY;
	array->data = malloc(sizeof(void*) * array->capacity);
}

int arrayLength(Array *array)
{
	return array->length;
}

void arrayPush(Array *array, void *data)
{
	/**
	 * If the array is at capacity, double
	 * the capacity.
	 */
	if (array->length == array->capacity)
	{
		array->capacity *= 2; 
		array->data = realloc(array->data, sizeof(void*) * array->capacity); 
	}

	array->data[array->length] = data; 
	array->length++;
}

void arraySet(Array *array, unsigned int index, void *data)
{
	/**
	 * Pad the array with empty values
	 * until we hit the selected index.
	 */
	while (array->length <= index)
	{
		arrayPush(array, NULL);
	}

	array->data[index] = data;
}

void *arrayPop(Array *array)
{
	void **data = array->data[array->length];
	arrayRemove(array, array->length);
	return data;
}

void *arrayGet(Array *array, unsigned int index)
{
	if (index >= array->length)
	{
		return NULL;
	}
	return array->data[index];
}

void arrayRemove(Array *array, unsigned int index)
{
	if (index >= array->length)
	{
		return;
	}

	array->data[index] = NULL;

	/**
	 * Remove any trailing null values.
	 */
	for (int i = array->length; i >  0; i--)
	{
		if (array->data[i - 1] != NULL)
		{
			break;
		}

		array->length--;

		if (array->length == array->capacity / 4 && array->capacity > ARRAY_INITIAL_CAPACITY)
		{
			array->capacity /= 2;
			array->data = realloc(array->data, sizeof(void*) * array->capacity); 
		}
	}
}

void arrayDestroy(Array *array)
{
	free(array->data);
}

void arrayEmpty(Array *array)
{
	arrayDestroy(array);
	arrayInit(array);	
}

