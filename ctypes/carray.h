#ifndef __CARRAY_H__
#define __CARRAY_H__

#include <stdlib.h>
#include <string.h>


typedef struct {
    void* items;
    int   length;
    int   capacity;
} Array;


int array_len(Array* ptr);

int array_cap(Array* ptr);

int array_end(Array* ptr);

void* array_index(Array* ptr, size_t type, int pos);

void array_clear(Array* ptr, size_t type);

Array* array_init(size_t type, int cap);

void array_free(Array* ptr);

int array_copy(Array* dst, Array* src, size_t type);

Array* array_append(Array* ptr, void* item, size_t type);

Array* array_extend(Array* dst, Array* src, size_t type);

void* array_pop(Array* ptr, size_t type);

void array_map(Array* ptr, void (*func)(const void*), size_t type);

void array_sort(Array* ptr, int (*func)(const void*, const void*), size_t type);

Array* array_reverse(Array* ptr, size_t type);

Array* array_filter(Array* ptr, int (*func)(const void*), size_t type);

Array* array_slice(Array* ptr, int start, int stop, size_t type);

#endif // __CARRAY_H__
