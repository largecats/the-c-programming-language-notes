/*
Exercise 8-6. The standard library function calloc(n,size) returns a pointer to n objects of size size, with the storage
initialized to zero. Write calloc, by calling malloc or by modifying it.
*/

#include <stdio.h>
#include "../header.h"

void *calloc1(unsigned n, unsigned size);

int main() {
    int *p = NULL;
    int i, N;

    N = 10;

    p = calloc1(N, sizeof *p);
    if (p == NULL) {
        printf("main: no space available\n");

    } else {
        for(i=0; i <= N; i++) {
            printf("%d", *p++);
        }
        printf("\n");
        free(p);
    }
    return 0;
}

/*
$ gcc chapter8/8.7/exercise_8-6/main.c chapter8/8.7/malloc.c helper_functions.c -o chapter8/8.7/exercise_8-6/result.out

$ chapter8/8.7/exercise_8-6/result.out
00000000000
*/

void *calloc1(unsigned n, unsigned size) {
    char *p, *originalP;
    unsigned nbytes, i;

    nbytes = n * size;
    p = malloc1(nbytes);
    originalP = p;
    for (i=0; i<nbytes; i++) {
        *(p++) = 0;
    }
    return originalP;
}