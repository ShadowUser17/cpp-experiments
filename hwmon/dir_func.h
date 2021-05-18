#ifndef __DIR_FUNC_H__
#define __DIR_FUNC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>


void print_errno(void) {
    fprintf(stderr, "%s\n", strerror(errno));
}


int str_to_id(const char *str_item, const int str_size) {
    int str_id = 0;

    for(int counter = 0; counter < strnlen(str_item, str_size); counter++) {
        str_id = str_id + (int)str_item[counter];
    }

    return str_id;
}


struct dirent *get_dir_items(const char *dir_path, int *items_count) {
    DIR *dir_ptr = opendir(dir_path);

    if(dir_ptr == NULL) {
        print_errno();
        return NULL;
    }

    struct dirent *dir_items = (struct dirent*)malloc(sizeof(struct dirent));

    if(dir_items == NULL) {
        print_errno();
        return NULL;
    }

    *items_count = 0;
    struct dirent *item_ptr = NULL;

    while((item_ptr = readdir(dir_ptr)) != NULL) {
        if(item_ptr->d_name[0] == '.') continue;
        /*if(strncmp(item_ptr->d_name, ".", 256) == 0) continue;
        if(strncmp(item_ptr->d_name, "..", 256) == 0) continue;*/

        memcpy(&dir_items[*items_count], item_ptr, sizeof(struct dirent));
        *items_count += 1;

        dir_items = (struct dirent*)realloc(dir_items, (sizeof(struct dirent) * (*items_count + 1)));

        if(dir_items == NULL) {
            print_errno();
            return NULL;
        }
    }

    closedir(dir_ptr);
    return dir_items;
}


void sort_dir_items(struct dirent *dir_items, int items_count) {
    struct dirent *item_tmp = (struct dirent*)malloc(sizeof(struct dirent));

    for(int counter1 = 0; counter1 < items_count; counter1++) {

        for(int counter2 = counter1 + 1; counter2 < items_count; counter2++) {

            if(str_to_id(dir_items[counter1].d_name, 256) > str_to_id(dir_items[counter2].d_name, 256)) {
                memcpy(item_tmp, &dir_items[counter1], sizeof(struct dirent));
                memcpy(&dir_items[counter1], &dir_items[counter2], sizeof(struct dirent));
                memcpy(&dir_items[counter2], item_tmp, sizeof(struct dirent));
            }
        }
    }

    free(item_tmp);
}


void print_dir_items(struct dirent *dir_items, int items_count) {
    fprintf(stdout, "items: %d\n", items_count);

    for(int counter = 0; counter < items_count; counter++) {

        switch(dir_items[counter].d_type) {
            case DT_DIR: fprintf(stdout, "DIR: %s\n", dir_items[counter].d_name); break;
            case DT_CHR: fprintf(stdout, "CHR: %s\n", dir_items[counter].d_name); break;
            case DT_BLK: fprintf(stdout, "BLK: %s\n", dir_items[counter].d_name); break;
            case DT_LNK: fprintf(stdout, "LNK: %s\n", dir_items[counter].d_name); break;
            case DT_REG: fprintf(stdout, "REG: %s\n", dir_items[counter].d_name); break;
            case DT_WHT: fprintf(stdout, "WTH: %s\n", dir_items[counter].d_name); break;

            case DT_SOCK: fprintf(stdout, "SOCK: %s\n", dir_items[counter].d_name); break;
            case DT_FIFO: fprintf(stdout, "FIFO: %s\n", dir_items[counter].d_name); break;
            case DT_UNKNOWN: fprintf(stdout, "UNKNOWN: %s\n", dir_items[counter].d_name); break;
        }
    }
}


char **dir_items_to_string(const char *dir_root, int root_size, struct dirent *dir_items, int items_count) {
    char **str_items = (char**)malloc(sizeof(char*) * items_count);

    if(str_items == NULL) {
        print_errno();
        return NULL;
    }

    root_size += 1;
    int dir_item_size = 0;

    for(int counter = 0; counter < items_count; counter++) {
        dir_item_size = strnlen(dir_items[counter].d_name, 256) + 1;
        str_items[counter] = (char*)malloc(sizeof(char) * (root_size + dir_item_size));

        memcpy(str_items[counter], dir_root, (sizeof(char) * root_size));

        if (str_items[counter][root_size-2] != '/') {
            str_items[counter][root_size-1] = '/';
            memcpy(&str_items[counter][root_size], dir_items[counter].d_name, (sizeof(char) * dir_item_size));
        } else {
            memcpy(&str_items[counter][root_size-1], dir_items[counter].d_name, (sizeof(char) * dir_item_size));
        }

        //fprintf(stdout, "%s\n", str_items[counter]);
    }

    free(dir_items);
    return str_items;
}


struct dirent *filter_dir_items(struct dirent *dir_items, int *items_count, char *flt_string) {
    struct dirent *dir_new_items = NULL;
    int dir_new_count = 0;

    for(int counter = 0; counter < *items_count; counter++) {

        if(strstr(dir_items[counter].d_name, flt_string)) {

            if(dir_new_count == 0) {
                dir_new_items = (struct dirent*)malloc(sizeof(struct dirent));

            } else {
                dir_new_items = (struct dirent*)realloc(dir_new_items, sizeof(struct dirent));
            }

            if(dir_new_items == NULL) {
                print_errno();
                return NULL;
            }

            dir_new_count += 1;
            memcpy(&dir_new_items[dir_new_count-1], &dir_items[counter], sizeof(struct dirent));
        }
    }

    free(dir_items);
    *items_count = dir_new_count;
    return dir_new_items;
}


void free_str_items(char **str_items, int items_count) {
    for(int counter = (items_count - 1); counter > 0; counter--) {
        free(str_items[counter]);
    }

    free(str_items);
}


void print_str_items(char **str_items, int items_count) {
    for(int counter = 0; counter < items_count; counter++) {
        fprintf(stdout, "%s\n", str_items[counter]);
    }
}

#endif // __DIR_FUNC_H__
