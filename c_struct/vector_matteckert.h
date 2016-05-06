#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

/* An opaque pointer to a vector abstract data type. */
typedef struct vector *vector;

/* Allocate, initialize, and return a new vector that stores elements of size
 * `size`. If `freefn` is not NULL, it is used to free individual elements
 * upon removal. Note that `freefn` will be called on already free'd memory
 * if elements point to the same memory location. */
vector vector_new(size_t hint, size_t size, void (*freefn)(void *));

/* Free memory allocated by `vector_new`. If `v` has a non-NULL `free`
 * function, the remaining elements of `v` are passed to this function. */
void vector_free(vector v);

/* Get the logical size of `v`. */
size_t vector_size(vector v);

/* Add `elem` to the end of `v`. */
bool vector_add(vector v, void *elem);

/* Store the element at index `i` in `elem`. */
bool vector_get(vector v, size_t i, void *elem);

/* Remove the element at index `i`. If `elem` is not NULL, the object removed
 * is stored in `elem`. If `elem` is NULL and `v` has a non-NULL `free`
 * function, the element at index `i` is passed to this function. */
bool vector_remove(vector v, size_t i, void *elem);

/* Insert the element `elem` at index `i`. The indices of elements after the
 * insertion point increment by one. */
bool vector_insert(vector v, size_t i, void *elem);

/* Return `true` if `v` is empty; otherwise, return `false`. */
bool vector_empty(vector v);

/* Remove all elements from `v`. If `v` has a non-NULL `free` function, the
 * each element of `v` is passed to this function. */
bool vector_clear(vector v);


#endif
