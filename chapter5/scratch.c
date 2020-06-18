#include <stdio.h>

int main() {
    int i;
    // int counter = 0;
    // do {
    //     i = getchar();
    //     printf("%d\n", i);
    //     // printf("%c\n", i);
    //     // putchar(i);
    //     printf("counter = %d\n", counter++);
    // } while (i != EOF);

    while ((i = getchar()) != EOF) {
        printf("%d\n", i);
    }

    return 0;
}