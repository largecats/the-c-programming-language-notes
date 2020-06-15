/*
Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field
width; the converted number must be padded with blanks on the left if necessary to make it wide enough.
*/

#include <stdio.h>
#include<string.h>

void reverse(char s[]) {
    int i;

    for (i=0; i < strlen(s)-i; i++) {
        char temp = s[strlen(s)-1-i];
        s[strlen(s)-1-i] = s[i];
        s[i] = temp;
    }
}

void itoa(long n, char s[], int p) {
    int i;
    int sign = 0;

    if (n < 0) {
        sign = -1;
    }
    i = 0;
    do {
        int digit = (n % 10);
        s[i++] = sign < 0? -digit + '0': digit + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    while (i < p) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

int main() {
    char s[1000] = {'\0'};
    long n = -12345;
    itoa(n, s, 10);
    printf("n = %ld\n", n);
    printf("s = %s\n", s);

    return 0;
}

/*
n = -12345
s =     -12345
*/