/*
Exercise 8-8. Write a routine bfree(p,n) that will free any arbitrary block p of n characters into the free list maintained by
malloc and free. By using bfree, a user can add a static or external array to the free list at any time.
*/

#include <stdio.h>
#include "header.h"
#include "../../../helper_functions.h"

void bfree(void *p, unsigned n);

int main() {

    int *p = NULL;
    int i;

    p = malloc1(1000);
    if (p == NULL) {
        printf("main: no space available\n");

    } else {
        bfree(p, 2000);
    }
    return 0;
}

/*
$ gcc chapter8/8.7/exercise_8-8/main.c chapter8/8.7/exercise_8-8/malloc.c helper_functions.c -o chapter8/8.7/exercise_8-8/result.out

$ chapter8/8.7/exercise_8-8/result.out
*/

void bfree(void *p, unsigned n) {
    if (n < sizeof(Header)) {
        fprintf(stderr, "bfree: invalid size %u\n", n);
    }

    unsigned nunits = (n + sizeof(Header)-1) / sizeof(Header) + 1;
    Header *bp = (Header *) p;
    bp->s.size = nunits;
    free((void *)(bp+1));
}