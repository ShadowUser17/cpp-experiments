#include <stdlib.h>
#include <string.h>

#include "cstring.h"


String* string_init(char* ptr, int size)
{
    String* string = (String*)malloc(sizeof(String));
    if(!string) return NULL;

    if(ptr && (size > 0)) {
        string->items = (char*)calloc(size, sizeof(char));

        if(!string->items) {
            free((void*)string);
            return NULL;
        }

        memcpy((void*)string->items, (void*)ptr, (sizeof(char) + size));
        string->length = size;

    } else {
        string->length = 0;
        string->items = (char*)malloc(sizeof(char));

        if(!string->items) {
            free((void*)string);
            return NULL;
        }

        string->items = '\0';
    }

    return string;
}


void string_free(String* ptr)
{
    if(ptr) {
        if(ptr->items) free((void*)ptr->items);

        free((void*)ptr);
    }
}
