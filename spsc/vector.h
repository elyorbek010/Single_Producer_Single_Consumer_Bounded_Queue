#ifndef VECTOR_H
#define VECTOR_H

#define DEBUG 0

#include "stddef.h"

typedef struct vector_t vector_t;

typedef enum vector_ret_t
{
	VECTOR_SUCCESS = 0,
	VECTOR_FAILURE = 1,
	VECTOR_OVERFLOW,
	VECTOR_UNDERFLOW
} vector_ret_t;

/**
 * Create a circular vector with `capacity` elements at most.
 *
 * RETURN VALUES:
 * vector_t pointer
 * NULL pointer -- when failed to allocate memory or 0 capacity
 *
 * [in] - capacity
 */
vector_t* vector_create(size_t capacity);

/**
 * Destroy the vector.
 *
 * RETURN VALUES:
 * VECTOR_SUCCESS -- vector is destroyed
 * VECTOR_FAILURE -- vector is invalid
 *
 * [in] - vector
 */
vector_ret_t vector_destroy(vector_t* vector);

/**
 * Add an element to the vector.
 *
 * RETURN VALUES:
 * VECTOR_SUCCESS
 * VECTOR_OVERFLOW -- vector is full, can not accept new data
 * VECTOR_FAILURE -- vector or element is invalid, or malloc failed when enlarging vector
 *
 * [in] - vector, element
 */
vector_ret_t vector_push(vector_t* vector, void* element);

/**
 * Remove an element from the vector.
 * Block the thread, when vector is empty, waiting for new data.
 *
 * RETURN VALUES:
 * VECTOR_SUCCESS
 * VECTOR_UNDERFLOW -- vector is empty
 * VECTOR_FAILURE -- vector or p_element is invalid
 *
 * [in] - vector
 * [out] - p_element
 */
vector_ret_t vector_pop(vector_t* vector, void** p_element);

#endif // VECTOR_H

