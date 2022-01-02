#include "cstring.h"


String* string_init(void) {
    String* string = (String*)malloc(sizeof(String));
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


void string_free(String* ptr) {
    if(!ptr) {
        if(ptr->items) free(ptr->items);

        free(ptr);
    }
}
