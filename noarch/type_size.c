#include <stdio.h>


int main(void)
{
    printf("long double: %u\n", sizeof(long double));
    printf("long long:   %u\n", sizeof(long long));
    printf("double:      %u\n", sizeof(double));
    printf("long:        %u\n", sizeof(long));
    printf("void*:       %u\n", sizeof(void*));
    printf("float:       %u\n", sizeof(float));
    printf("int:         %u\n", sizeof(int));
    printf("short:       %u\n", sizeof(short));
    printf("char:        %u\n", sizeof(char));

    return 0;
}
