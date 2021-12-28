#ifndef __CARRAY_H__
#define __CARRAY_H__

#include <stdlib.h>
#include <string.h>


struct Array {
    void* items;
    int   length;
    int   capacity;
};


int array_len(struct Array* ptr) {
    if(ptr != NULL) {
        return ptr->length;
    }

    return -1;
}


int array_cap(struct Array* ptr) {
    if(ptr != NULL) {
        return ptr->capacity;
    }

    return -1;
}


void* array_index(struct Array* ptr, size_t type, int pos) {
    if(ptr != NULL) {
        if((pos > -1) && (pos < ptr->capacity)) {
            return (ptr->items + (type * pos));
        }
    }

    return NULL;
}


struct Array* array_init(size_t type, int cap) {
    struct Array* array = (struct Array*)malloc(sizeof(struct Array));

    if(array == NULL) return NULL;

    array->items = NULL;
    array->length = 0;
    array->capacity = 0;

    if(cap < 10) cap = 10;

    array->items = calloc(cap, type);

    if(array->items == NULL) return NULL;

    array->capacity = cap;

    memset(array->items, 0, (type * cap));
    return array;
}


void array_free(struct Array* ptr) {
    if(ptr != NULL) {
        if(ptr->items != NULL) free(ptr->items);

        free(ptr);
    }
}


int array_copy(struct Array* dst, struct Array* src, size_t type) {
    if((dst != NULL) && (src != NULL)) {
        void* dst_index = NULL;
        void* src_index = NULL;
        int it = 0;

        while(it < src->length) {
            dst_index = array_index(dst, type, it);
            src_index = array_index(src, type, it);

            if((dst_index != NULL) && (src_index != NULL)) {
                memcpy(dst_index, src_index, type);
                dst->length += 1;
                it += 1;

            } else break;
        }

        return it;
    }

    return -1;
}


struct Array* array_append(struct Array* ptr, void* item, size_t type) {
    if(ptr != NULL) {
        if(ptr->length < ptr->capacity) {
            memcpy(array_index(ptr, type, ptr->length), item, type);
            ptr->length += 1;
            return ptr;

        } else {
            struct Array* new_ptr = array_init(type, (ptr->capacity + 10));

            if(new_ptr != NULL) {
                if(array_copy(new_ptr, ptr, type) > 0) {
                    array_free(ptr);

                    memcpy(array_index(new_ptr, type, new_ptr->length), item, type);
                    new_ptr->length += 1;
                    return new_ptr;

                } else {
                    array_free(new_ptr);
                    return ptr;
                }
            }
        }
    }

    return NULL;
}

#endif // __CARRAY_H__
