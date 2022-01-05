#ifndef __CSTRING_H__
#define __CSTRING_H__

typedef struct {
    char* items;
    int   length;
} String;


String* string_init(void);

void string_free(String* ptr);

#endif // __CSTRING_H__
