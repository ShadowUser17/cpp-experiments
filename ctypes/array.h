#ifndef __ARRAY__
#define __ARRAY__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


struct Array {
    void* items;
    int   length;
    int   capacity;
};


int array_len(struct Array* ptr) {
    if(ptr != NULL) {
        return ptr->length;
    }

    return 0;
}


int array_cap(struct Array* ptr) {
    if(ptr != NULL) {
        return ptr->capacity;
    }

    return 0;
}


void* array_index(struct Array* ptr, size_t type, int pos) {
    if(ptr != NULL) {
        return ptr->items + (type * pos);
    }

    return NULL;
}


struct Array* array_init(size_t type, int cap) {
    struct Array* array = (struct Array*)malloc(sizeof(struct Array));

    if(array == NULL) {
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    if(cap <= 1) { cap = 10; }

    array->items = calloc(cap, type);

    if(array->items == NULL) {
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    array->length = 0;
    array->capacity = cap;

    memset(array->items, 0, (type * array->capacity));
    return array;
}


void array_free(struct Array* ptr) {
    if(ptr != NULL) {
        free(ptr->items);
        free(ptr);
    }
}

#endif // __ARRAY__
