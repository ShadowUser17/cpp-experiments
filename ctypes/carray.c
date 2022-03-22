#include <stdlib.h>
#include <string.h>

#include "carray.h"


int array_len(Array* ptr) {
    if(ptr) return ptr->length;

    return -1;
}


int array_cap(Array* ptr) {
    if(ptr) return ptr->capacity;

    return -1;
}


int array_end(Array* ptr) {
    if(!ptr) return -1;

    return (ptr->length - 1);
}


void* array_index(Array* ptr, size_t type, int pos) {
    if(ptr) {
        if((pos > -1) && (pos < ptr->capacity)) {
            return ((char*)ptr->items + (type * pos));
        }
    }

    return NULL;
}


void array_clear(Array* ptr, size_t type) {
    if(ptr) {
        memset(ptr->items, 0, (type * ptr->length));
        ptr->length = 0;
    }
}


Array* array_init(size_t type, int cap) {
    Array* array = (Array*)malloc(sizeof(Array));
    if(!array) return NULL;

    if(cap < 10) cap = 10;

    array->items = calloc(cap, type);
    if(!array->items) {
        free((void*)array);
        return NULL;
    }

    array->length = 0;
    array->capacity = cap;
    return array;
}


void array_free(Array* ptr) {
    if(ptr) {
        if(ptr->items) free(ptr->items);

        free((void*)ptr);
    }
}


int array_copy(Array* dst, Array* src, size_t type) {
    if(dst && src) {
        if(dst->capacity > src->length) {
            memcpy(dst->items, src->items, (type * src->length));
            dst->length = src->length;

        } else {
            void* new_items = realloc(dst->items, (type * (src->length + 10)));
            if(!new_items) return -1;

            dst->items = new_items;
            dst->capacity = src->length + 10;

            memcpy(dst->items, src->items, (type * src->length));
            dst->length = src->length;
        }

        return dst->length;
    }

    return -1;
}


Array* array_append(Array* ptr, void* item, size_t type) {
    if(ptr && item) {
        if(ptr->length < ptr->capacity) {
            memcpy(array_index(ptr, type, ptr->length), item, type);
            ptr->length += 1;

        } else {
            void* new_items = realloc(ptr->items, (type * (ptr->capacity + 10)));
            if(!new_items) return ptr;

            ptr->items = new_items;
            ptr->capacity += 10;

            memcpy(array_index(ptr, type, ptr->length), item, type);
            ptr->length += 1;
        }

        return ptr;
    }

    return NULL;
}


Array* array_extend(Array* dst, Array* src, size_t type) {
    if(dst && src) {
        if((dst->length + src->length) < dst->capacity) {
            memcpy(array_index(dst, type, dst->length), src->items, (type * src->length));
            dst->length = (dst->length + src->length);

        } else {
            void* new_items = realloc(dst->items, (type * (dst->length + src->length + 10)));
            if(!new_items) return dst;

            dst->items = new_items;
            dst->capacity = (dst->length + src->length + 10);

            memcpy(array_index(dst, type, dst->length), src->items, (type * src->length));
            dst->length = (dst->length + src->length);
        }

        return dst;
    }

    return NULL;
}


void* array_pop(Array* ptr, size_t type) {
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


void array_map(Array* ptr, void (*func)(const void*), size_t type) {
    if(ptr && func) {
        for(int it = 0; it < ptr->length; it++) {
            func(array_index(ptr, type, it));
        }
    }
}


void array_sort(Array* ptr, int (*func)(const void*, const void*), size_t type) {
    if(ptr && func) {
        qsort(ptr->items, ptr->length, type, func);
    }
}


Array* array_reverse(Array* ptr, size_t type) {
    if(ptr) {
        if(ptr->length > 1) {
            Array* new_ptr = array_init(type, ptr->capacity);
            if(!new_ptr) return NULL;

            void* item = NULL;
            for(int it = ptr->length - 1; it >= 0; it--) {
                item = array_index(ptr, type, it);
                new_ptr = array_append(new_ptr, item, type);
            }

            array_free(ptr);
            return new_ptr;
        }
    }

    return NULL;
}


Array* array_filter(Array* ptr, int (*func)(const void*), size_t type) {
    if(ptr && func) {
        Array* new_ptr = array_init(type, 0);
        if(!new_ptr) return NULL;

        void* item = NULL;
        for(int it = 0; it < ptr->length; it++) {
            item = array_index(ptr, type, it);

            if(func(item)) {
                new_ptr = array_append(new_ptr, item, type);
            }
        }

        return new_ptr;
    }

    return NULL;
}


Array* array_slice(Array* ptr, int start, int stop, size_t type) {
    if(ptr) {
        if((start < 0) || (start >= stop) || (stop > ptr->length)) return NULL;

        Array* new_ptr = array_init(type, (stop - start + 10));
        if(!new_ptr) return NULL;

        new_ptr->length = stop - start;
        memcpy(new_ptr->items, array_index(ptr, type, start), (type * new_ptr->length));
        return new_ptr;
    }

    return NULL;
}
