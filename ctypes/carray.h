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


int array_end(struct Array* ptr) {
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


void array_clear(struct Array* ptr, size_t type) {
    if(ptr) {
        memset(ptr->items, 0, (type * ptr->length));
        ptr->length = 0;
    }
}


struct Array* array_init(size_t type, int cap) {
    struct Array* array = (struct Array*)malloc(sizeof(struct Array));
    if(!array) return NULL;

    if(cap < 10) cap = 10;

    array->items = calloc(cap, type);
    if(!array->items) {
        free(array);
        return NULL;
    }

    array->length = 0;
    array->capacity = cap;
    return array;
}


void array_free(struct Array* ptr) {
    if(ptr) {
        if(ptr->items) free(ptr->items);

        free(ptr);
    }
}


int array_copy(struct Array* dst, struct Array* src, size_t type) {
    if(dst && src) {
        if(dst->capacity > src->length) {
            memcpy(dst->items, src->items, (type * src->length));
            dst->length = src->length;

        } else {
            void* new_items = realloc(dst->items, (type * (src->length + 10)));
            if(!new_items) return -1;

            dst->items = new_items;
            memcpy(dst->items, src->items, (type * src->length));

            dst->length = src->length;
            dst->capacity = src->length + 10;
        }

        return dst->length;
    }

    return -1;
}


struct Array* array_append(struct Array* ptr, void* item, size_t type) {
    if(ptr && item) {
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


struct Array* array_extend(struct Array* dst, struct Array* src, size_t type) {
    if(dst && src) {
        if((dst->length + src->length) < dst->capacity) {
            memcpy(array_index(dst, type, dst->length), src->items, (type * src->length));
            dst->length = (dst->length + src->length);

        } else {
            void* ptr = realloc(dst->items, (type * (dst->length + src->length + 10)));
            if(!ptr) return dst;

            dst->items = ptr;
            dst->capacity = (dst->length + src->length + 10);

            for(int it = 0; it < src->length; it++) {
                ptr = array_index(src, type, it);
                memcpy(array_index(dst, type, dst->length), ptr, type);
                dst->length += 1;
            }
        }

        return dst;
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


void array_map(struct Array* ptr, void (*func)(const void*), size_t type) {
    if(ptr && func) {
        for(int it = 0; it < ptr->length; it++) {
            func(array_index(ptr, type, it));
        }
    }
}


void array_sort(struct Array* ptr, int (*func)(const void*, const void*), size_t type) {
    if(ptr && func) {
        qsort(ptr->items, ptr->length, type, func);
    }
}


struct Array* array_reverse(struct Array* ptr, size_t type) {
    if(ptr) {
        if(ptr->length > 1) {
            struct Array* new_ptr = array_init(type, ptr->capacity);
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


struct Array* array_filter(struct Array* ptr, int (*func)(const void*), size_t type) {
    if(ptr && func) {
        struct Array* new_ptr = array_init(type, 0);
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


struct Array* array_slice(struct Array* ptr, int start, int stop, size_t type) {
    if(ptr) {
        if((start < 0) || (start >= stop) || (stop > ptr->length)) return NULL;

        struct Array* new_ptr = array_init(type, (stop - start + 10));
        if(!new_ptr) return NULL;

        new_ptr->length = (stop - start);
        memcpy(new_ptr->items, array_index(ptr, type, start), (type * new_ptr->length));
        return new_ptr;
    }

    return NULL;
}

#endif // __CARRAY_H__
