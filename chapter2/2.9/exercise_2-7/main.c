/*
Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e, 1 changed into 0 and vice versa), leaving the others unchanged.
*/
#include <stdio.h>

void print_bits(unsigned x);
unsigned invert(unsigned x, int p, int n);

int main() {
    unsigned x = 118;
    int p = 5;
    int n = 4;
    unsigned result = invert(x, p, n);
    printf("x:\n");
    print_bits(x);
    printf("result:\n");
    print_bits(result);
}

/*
$ gcc chapter2/2.9/exercise_2-7/main.c -o chapter2/2.9/exercise_2-7/result.out

$ chapter2/2.9/exercise_2-7/result.out
x:
0000000001110110
result:
0000000001001010
*/

void print_bits(unsigned x) {
    for (int i=sizeof(x)*4-1; i>=0; i--) { // sizeof returns size in bytes
        if (x & (1<<i)) {
            putchar('1');
        }
        else {
            putchar('0');
        }
    }
    putchar('\n');
}

unsigned invert(unsigned x, int p, int n) {
    unsigned xMask = (~(~0<<n))<<(p-n+1);
    // print_bits(xMask);
    return (x ^ xMask);
    /*
    in exclusive OR, for bits that are 1 in xMask, if x has 1, result will be 0, if x has 0, result will be 1; for bits that are 0 in xMask, if x has 1, result will be 1, if x has 0, result will be 0
    */
}