#ifndef __CSTRING_H__
#define __CSTRING_H__

#include <stdlib.h>
#include <string.h>


struct String {
    char* items;
    int   length;
};


struct String* string_init(void) {
    struct String* string = (struct String*)malloc(sizeof(struct String));
    if(!string) return NULL;

    string->items = (char*)calloc(16, sizeof(char));
    if(!string->items) {
        free(string);
        return NULL;
    }

    string->items[15] = '\0';
    string->length = 15;

    return string;
}


void string_free(struct String* ptr) {
    if(!ptr) {
        if(ptr->items) free(ptr->items);

        free(ptr);
    }
}

#endif // __CSTRING_H__
