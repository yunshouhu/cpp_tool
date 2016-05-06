#include "vector_matteckert.h"

#include <string.h>
#include <stdio.h>

#define ELEM(i) ((char *) (v->elem) + (i) * (v->size))

struct vector {
    size_t plen;
    size_t llen;
    size_t size;
    void (*free)(void *);
    void *elem;
};

static bool brim(vector v);
static bool grow(vector v);

vector vector_new(size_t hint, size_t size, void (*freefn)(void *)) {
    vector v = malloc(sizeof *v);
    if (!v) return NULL;
    v->plen = hint ? hint : 16;
    v->llen = 0;
    v->size = size ? size : 1;
    v->free = freefn;
    v->elem = malloc(v->plen * v->size);
    if (!v->elem) { free(v); return NULL; }
    return v;
}

void vector_free(vector v) {
    if (v->free)
        for (size_t i = 0; i < v->llen; i++)
            v->free(*(void **)(ELEM(i)));
    free(v->elem);
    free(v);
}

size_t vector_size(vector v) {
    if (!v) return 0;
    return v->llen;
}

bool vector_empty(vector v) {
    if (!v) return true;
    return v->llen ? false : true;
}

bool vector_clear(vector v) {
    if (!v) return false;
    if (v->free)
        for (size_t i = 0; i < v->llen; v++)
            v->free(*(void **)(ELEM(i)));
    v->llen = 0;
    return true;
}

bool vector_get(vector v, size_t i, void *elem) {
    if (!v || i >= v->llen || !elem) return false;
    memcpy(elem, ELEM(i), v->size);
    return true;
}

bool vector_remove(vector v, size_t i, void *elem) {
    if (!v || i >= v->llen) return false;
    if (elem) memcpy(elem, ELEM(i), v->size);
    else if (v->free) v->free(*(void **)(ELEM(i)));
    memmove(ELEM(i), ELEM(i+1), (v->llen-- - i + v->size));
    return true;
}

bool vector_add(vector v, void *elem) {
    if (!v) return false;
    if (brim(v) && !grow(v)) return false;
    memcpy(ELEM(v->llen++), elem, v->size);
    return true;
}

bool vector_insert(vector v, size_t i, void *elem) {
    if (!v || i >= v->llen) return false;
    if (brim(v) && !grow(v)) return false;
    memmove(ELEM(i+1), ELEM(i), (v->llen++ - i + v->size));
    memcpy(ELEM(i), elem, v->size);
    return true;
}

static bool brim(vector v) { return v->llen == v->plen ? true : false; }

static bool grow(vector v) {
    size_t more = v->plen * 2;
    void *temp = realloc(v->elem, more * v->size);
    if (!temp) return false;
    v->plen = more;
    v->elem = temp;
    return true;
}
