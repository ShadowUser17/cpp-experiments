#include <stdio.h>


void after_exploit(void) {
    fprintf(stderr, "+-----------------------------------------+\n");
    fprintf(stderr, "| Congratulation! Your exploit is worked! |\n");
    fprintf(stderr, "+-----------------------------------------+\n");
}


int main(void) {
    char buff[33];

    for(int it = 0, tmp; (tmp = getchar()) != EOF; it++) {
        buff[it] = tmp;
    }

    fprintf(stdout, "\"%s\"\n", buff);

    return 0;
}
