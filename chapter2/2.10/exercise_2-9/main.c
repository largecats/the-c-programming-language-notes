/*
Exercise 2-9. In a two’s complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount.
*/

/*
x-1 turns the rightmost 1-bit in x to 0 and turns 0-bits to the right of the rightmost 1-bit to 1. In other words, x-1 inverts all bits to the right (inclusive) of the rightmost 1-bit in x. Thus, x & (x-1) turns all bits to the right (inclusive) of the rightmost 1-bit in x to 0.
*/

#include <stdio.h>

void print_bits(unsigned x);
int bitcount(unsigned x);

int main() {
    unsigned x = 118;
    print_bits(x);
    int result = bitcount(x);
    printf("%d\n", result);
}

/*
$ gcc chapter2/2.10/exercise_2-9/main.c -o chapter2/2.10/exercise_2-9/result.out

$ chapter2/2.10/exercise_2-9/result.out
0000000001110110
5
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

int bitcount(unsigned x) {
    int i;
    for (i=0; x != 0; x &= (x-1)) {
        i++;
    }
    return i;
}