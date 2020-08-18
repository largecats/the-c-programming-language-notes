/*
Exercise 3-4. In a two’s complement number representation, our version of itoa does not handle the largest negative
number, that is, the value of n equal to -(2^{wordsize-1}). Explain why not. Modify it to print that value correctly, regardless of the
machine on which it runs.
*/

/*
In the original itoa(), negative n is converted to positive by assigning n = - n. But recall that the range for signed long is -2^63 to 2^63-1. So if n is -2^63, taking -n gives 2^63, which exceeds the upper limit for signed long. So instead of making n positive, we directly deal with the negative n, and only take absolute value of the modulus.
*/

#include <stdio.h>
#include<string.h>

void reverse(char s[]);
void itoa(long n, char s[]);

int main() {
    char s[1000] = {'\0'};
    long n = -(~(1L<<63))-1;
    // long n = -10;
    itoa(n, s);
    printf("n = %ld\n", n);
    printf("s = %s\n", s);

    return 0;
}

/*
$ gcc chapter3/3.6/exercise_3-4/main.c -o chapter3/3.6/exercise_3-4/result.out

$ chapter3/3.6/exercise_3-4/result.out
n = -9223372036854775808
s = -9223372036854775808
*/

void reverse(char s[]) {
    int i;

    for (i=0; i < strlen(s)-i; i++) {
        char temp = s[strlen(s)-1-i];
        s[strlen(s)-1-i] = s[i];
        s[i] = temp;
    }
}

void itoa(long n, char s[]) {
    int i, sign;

    sign = (n<0)? -1: 1;
    i = 0;
    do {
        int digit = (n % 10);
        s[i++] = sign < 0? -digit + '0': digit + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
