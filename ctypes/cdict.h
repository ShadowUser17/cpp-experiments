#ifndef __CDICT_H__
#define __CDICT_H__

typedef struct {
    int   hash;
    int   size;
    void* item;
} DictItem;

#endif // __CDICT_H__
