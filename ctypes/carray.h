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
    if(ptr) return ptr->length;

    return -1;
}


int array_cap(struct Array* ptr) {
    if(ptr) return ptr->capacity;

    return -1;
}


int array_stop(struct Array* ptr) {
    if(!ptr) return -1;

    return (ptr->length - 1);
}


void* array_index(struct Array* ptr, size_t type, int pos) {
    if(ptr) {
        if((pos > -1) && (pos < ptr->capacity)) {
            return (ptr->items + (type * pos));
        }
    }

    return NULL;
}


struct Array* array_init(size_t type, int cap) {
    struct Array* array = (struct Array*)malloc(sizeof(struct Array));
    if(!array) return NULL;

    array->items = NULL;
    array->length = 0;
    array->capacity = 0;

    if(cap < 10) cap = 10;

    array->items = calloc(cap, type);
    if(!array->items) return NULL;

    array->capacity = cap;
    return array;
}


void array_free(struct Array* ptr) {
    if(ptr) {
        if(ptr->items) free(ptr->items);

        free(ptr);
    }
}


void array_reset(struct Array* ptr, size_t type) {
    if(ptr) {
        memset(ptr->items, 0, (type * ptr->length));
        ptr->length = 0;
    }
}


int array_copy(struct Array* dst, struct Array* src, size_t type) {
    if(dst && src) {
        if(dst->capacity > src->length) {
            memcpy(dst->items, src->items, (type * src->length));
            dst->length = src->length;

        } else {
            void* items = NULL;
            items = realloc(dst->items, (type * (src->length + 10)));
            if(!items) return -1;

            dst->items = items;
            memcpy(dst->items, src->items, (type * src->length));
            dst->length = src->length;
            dst->capacity = src->length + 10;
        }

        return dst->length;
    }

    return -1;
}


struct Array* array_append(struct Array* ptr, void* item, size_t type) {
    if(ptr) {
        if(ptr->length < ptr->capacity) {
            memcpy(array_index(ptr, type, ptr->length), item, type);
            ptr->length += 1;
            return ptr;

        } else {
            struct Array* new_ptr = array_init(type, (ptr->capacity + 10));

            if(new_ptr) {
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


void* array_pop(struct Array* ptr, size_t type) {
    if(ptr) {
        int pos = ptr->length - 1;
        if(pos < 0) return NULL;

        void* item = array_index(ptr, type, pos);
        if(item) {
            ptr->length -= 1;
            return item;
        }
    }

    return NULL;
}


void array_map(struct Array* ptr, void (*func)(void*), size_t type) {
    if(ptr) {
        for(int it = 0; it < ptr->length; it++) {
            func(array_index(ptr, type, it));
        }
    }
}

#endif // __CARRAY_H__
