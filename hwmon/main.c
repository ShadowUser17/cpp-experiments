#include <stdio.h>
#include <stdlib.h>

#include "dir_func.h"

const char *HWMON_PATH = "/sys/class/hwmon";


int main(int argc, char **argv) {
    int hwmons_size = 0;
    struct dirent *hwmons = get_dir_items(argv[1], &hwmons_size);
    //struct dirent *hwmons = get_dir_items(HWMON_PATH, &hwmons_size);

    if(hwmons == NULL) {
        print_errno();
        return 1;
    }

    sort_dir_items(hwmons, hwmons_size);
    print_dir_items(hwmons, hwmons_size, -1);
    free(hwmons);

    /*char **str_items = dir_items_to_string(argv[1], strlen(argv[1]), hwmons, hwmons_size);
    int str_size = hwmons_size;
    //char **str_items = dir_items_to_string(HWMON_PATH, strlen(HWMON_PATH), hwmons, hwmons_size);

    //print_str_items(str_items, hwmons_size);

    for(int counter = 0; counter < str_size; counter++) {
        hwmons = get_dir_items(str_items[counter], &hwmons_size);
        //hwmons = filter_dir_items(hwmons, &hwmons_size, argv[2]);
        //hwmons = filter_dir_items(hwmons, &hwmons_size, "input");

        if(hwmons != NULL) {
            printf("%s\n", str_items[counter]);
            print_dir_items(hwmons, hwmons_size, -1);
            free(hwmons);
        }
    }

    free_str_items(str_items, hwmons_size);*/
    return 0;
}