/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s. In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    int i;

    for (i=0; i < strlen(s)-i; i++) {
        char temp = s[strlen(s)-1-i];
        s[strlen(s)-1-i] = s[i];
        s[i] = temp;
    }
}

void itob(int n, char s[], int b) {
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        char digit = n % b;
        s[i++] = digit <= 9? digit + '0': digit + 'A' - 10;
    } while ((n /= b) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[1000] = {'\0'};
    long n = 30;
    itob(n, s, 16);
    printf("n = %ld\n", n);
    printf("s = %s\n", s);

    return 0;
}