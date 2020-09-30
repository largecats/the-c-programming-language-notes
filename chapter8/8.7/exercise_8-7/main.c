/*
Exercise 8-7. malloc accepts a size request without checking its plausibility; free believes that the block it is asked to free
contains a valid size field. Improve these routines so they make more pains with error checking.
*/

#include <stdio.h>
#include "../header.h"
#include "../../../helper_functions.h"

int main() {
    // Header h;
    // print_variable(h.s.size); // nothing
    // Header *p;
    // print_variable(p->s.size); // segmentation fault

    int *p = NULL;
    int i, N;

    N = 1000000;

    p = malloc1(N);
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

    return 0;
}

/*
$ gcc chapter8/8.7/exercise_8-7/main.c chapter8/8.7/exercise_8-7/malloc.c helper_functions.c -o chapter8/8.7/exercise_8-7/result.out

$ chapter8/8.7/exercise_8-7/result.out
malloc1: exceeded maximum number of bytes 10000
main: no space available
*/