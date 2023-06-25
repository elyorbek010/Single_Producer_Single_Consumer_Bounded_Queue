/*
 * SPSC Bounded Vector.
 *
 * Vector's working principles:
 * Vector of size 3
 *   |1|2|3|.|
 *    |     |
 * [begin  end)
 *
 * Begin index is inclusive, the element at that index exists
 * End index is exclusive, the element at that index does not exist
 *
 * Corner cases:
 *	'begin == end' -- vector is empty, because 'end' is exclusive
 *	'next(end) == begin' -- vector is full, because 'end' catched up 'begin
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdatomic.h>

#include "vector.h"
#include "debug.h"

#define CHECK_AND_RETURN_IF_NOT_EXIST(pointer_object) \
	do                                                \
	{                                                 \
		if (pointer_object == NULL)                   \
		{                                             \
			debug_print("Object does not exist\n");   \
			return VECTOR_FAILURE;                    \
		}                                             \
	} while (0)

struct vector_t
{
	size_t capacity;
	size_t begin; // begin index is inclusive
	size_t end;  // end index is exclusive

	void *element[];
};

/*
 * FUNCTION DECLARATIONS
 */

vector_t *vector_create(const size_t capacity);
vector_ret_t vector_destroy(vector_t *vector);

vector_ret_t vector_push(vector_t *vector, void *element);

vector_ret_t vector_pop(vector_t *vector, void **element);

static inline size_t vector_next_index(const size_t index, const size_t capacity);

/*
 * FUNCTION DEFINITIONS
 */

vector_t *vector_create(size_t capacity)
{
	vector_t *vector = malloc(sizeof(*vector) + (capacity + 1) * sizeof(vector->element[0]));

	if (vector == NULL) // condition that malloc() failed
	{
		debug_print("Not enough memory for capacity: %zu\n", capacity);
		return NULL;
	}

	vector->begin = vector->end = 0;
	vector->capacity = capacity;

	return vector;
}

vector_ret_t vector_destroy(vector_t *vector)
{
	CHECK_AND_RETURN_IF_NOT_EXIST(vector);

	free(vector);

	return VECTOR_SUCCESS;
}

vector_ret_t vector_push(vector_t *vector, void *element)
{
	CHECK_AND_RETURN_IF_NOT_EXIST(vector);

	atomic_thread_fence(memory_order_acquire);
	size_t begin = vector->begin;
	size_t end = vector->end;

	size_t next_end = vector_next_index(end, vector->capacity);

	// Check if vector is FULL
	if (next_end == begin)
		return VECTOR_OVERFLOW;

	void *dest = vector->element + end;

	vector->element[end] = element;
	vector->end = next_end;
	atomic_thread_fence(memory_order_release);

	return VECTOR_SUCCESS;
}

vector_ret_t vector_pop(vector_t *vector, void **p_element)
{
	CHECK_AND_RETURN_IF_NOT_EXIST(vector);
	CHECK_AND_RETURN_IF_NOT_EXIST(p_element);

	atomic_thread_fence(memory_order_acquire);
	size_t begin = vector->begin;
	size_t end = vector->end;

	// Check if vector is EMPTY
	if (begin == end)
		return VECTOR_UNDERFLOW;

	*p_element = vector->element[begin];
	vector->begin = vector_next_index(begin, vector->capacity);
	atomic_thread_fence(memory_order_release);

	return VECTOR_SUCCESS;
}

static inline size_t vector_next_index(const size_t index, const size_t capacity)
{
	// note: actual allocated capacity is 'capacity + 1'
	return (index + 1) % (capacity + 1);
}