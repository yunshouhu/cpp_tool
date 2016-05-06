#ifndef __H_CEEF6E83FC3C441784ECEC6539B91AEB__
#define __H_CEEF6E83FC3C441784ECEC6539B91AEB__

#include <stdlib.h>
#include <string.h>

enum {
	VECE_OK = 0,
	VECE_NULL_POINTER,
	VECE_OUT_OF_MEMORY,
	VECE_OUT_OF_BOUNDS
};

struct vector {
	size_t count;
	size_t max;
	void **mem;
};


#if defined(WIN32) && !defined(__cplusplus)
#define inline __inline

#endif



inline static size_t vector_capacity(const struct vector *vec)
{
	return vec ? vec->max : 0;
}

inline static size_t vector_count(const struct vector *vec)
{
	return vec ? vec->count : 0;
}

int vector_add(struct vector *vec, void *item);

int vector_apply(struct vector *vec, void (*func)(void *));

int vector_delete(struct vector *vec, size_t index, void **item);

int vector_free(struct vector *vec);

int vector_get(struct vector *vec, size_t index, void **item);

int vector_init(struct vector *vec);

int vector_reserve(struct vector *vec, size_t size);

int vector_set(struct vector *vec, size_t index, void *item);

int vector_swap(struct vector *vec, size_t idx1, size_t idx2);

#endif
