/*
Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../helper_functions.h"
#include "calc.h"

int getline(char *s, int lim);
int atoi(char *s);
void itoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);

int main() {
    /* getline */
    int l;
    char s0[MAXLINE];
    while ((l = getline(s0, MAXLINE)) > 0) {
        print_string(s0);
    }

    /* atoi */
    char s1[] = "12345";
    print_variable(atoi(s1));

    /* itoa */
    int n = 12345;
    char s2[MAXLINE];
    itoa(n, s2);
    print_string(s2);

    /* strindex */
    char s3[] = "hello Neo";
    char s4[] = "Neo";
    print_variable(strindex(s3, s4));
}

int getline(char *s, int lim) {
    int c;
    char *original_s = s;

    while (lim > 0 && (c=getchar()) != EOF && c != '\n') {
        *s++ = c;
        lim--;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - original_s;
}

int atoi(char *s) {
    int i;

    i = 0;
    for (; *s >= '0' && *s <= '9'; s++) {
        i = 10 * i + (*s - '0');
    }
    return i;
}

void itoa(int n, char *s) {
    int sign;
    char *original_s;

    original_s = s;
    sign = (n<0)? -1: 1;
    do {
        int digit = (n % 10);
        *s++ = sign < 0? -digit + '0': digit + '0';
    } while ((n /= 10) != 0);
    if (sign < 0) {
        *s++ = '-';
    }
    *s = '\0';
    reverse(original_s);
}

void reverse(char *s) {
    char *t = s + strlen(s) - 1;

    for (; t > s; t--, s++) {
        int temp = *t;
        *t = *s;
        *s = temp;
    }
}

int strindex(char *s, char *t) {
    char *original_s = s ;
    char *original_t = t;

    for (; *s != '\0'; s++) {
        char *s1 = s;
        for (t = original_t; *t != '\0' & *s1 == *t; s1++, t++) {
            ;
        }
        if (t-original_t > 0 && *t == '\0') {
            return s - original_s;
        }
    }
    return -1;
}