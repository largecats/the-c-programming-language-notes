/*
Exercise 2-8. Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n positions.
*/
#include <stdio.h>

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

unsigned rightrot(unsigned x, int n) {
    unsigned xRightMask = ~(~0<<n);
    unsigned xRightBits = (x & xRightMask)<<(sizeof(x)*4-n);
    return (xRightBits | (x>>n));
}

main() {
    unsigned x = 118;
    int n = 4;
    unsigned result = rightrot(x, n);
    printf("x:\n");
    print_bits(x);
    printf("result:\n");
    print_bits(result);
}

/*
x:
0000000001110110
result:
0110000000000111
*/