#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "dir_func.h"


int main(const int argc, const char **argv) {
    int hwmons_size = 0;
    struct dirent *hwmons = get_dir_items(HWMON_PATH, &hwmons_size);

    if(hwmons == NULL) {
        print_errno();
        return 1;
    }

    sort_dir_items(hwmons, hwmons_size);

    char **str_items = dir_items_to_string(HWMON_PATH, strlen(HWMON_PATH), hwmons, hwmons_size);
    free(hwmons);

    print_str_items(str_items, hwmons_size);

    free_str_items(str_items, hwmons_size);
    //free(hwmons);
    return 0;
}