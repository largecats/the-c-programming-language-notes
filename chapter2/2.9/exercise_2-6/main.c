/*
Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/

#include <stdio.h>

void print_bits(unsigned x);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main() {
    unsigned x = 118;
    int p = 4;
    int n = 3;
    unsigned y = 83;
    unsigned result = setbits(x, p, n, y);
    printf("x:\n");
    print_bits(x);
    printf("y:\n");
    print_bits(y);
    printf("result:\n");
    print_bits(result);
}

/*
$ gcc chapter2/2.9/exercise_2-6/main.c -o chapter2/2.9/exercise_2-6/result.out

$ chapter2/2.9/exercise_2-6/result.out
x:
0000000001110110
y:
0000000001010011
result:
0000000001101110
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

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned yMask = ~(~0<<n);
    unsigned xMask = ~(yMask<<(p-n+1));
    // printf("xMask = ");
    // print_bits(xMask);
    // printf("yMask = ");
    // print_bits(yMask);
    // printf("x & xMask = ");
    // print_bits(x & xMask);
    // printf("(y & yMask)<<p-n+1 = ");
    // print_bits((y & yMask)<<p-n+1);
    return ((x & xMask) | ((y & yMask)<<p-n+1));
}