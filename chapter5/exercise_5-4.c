/*
Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise.
*/

#include <stdio.h>
#include <string.h>
#include "../helper_functions.h"

int strend(char *s, char *t);

int main() {
    char s[] = "hello Neo";
    char t[] = "Neo";

    printf("%d", strend(s, t));
}

int strend(char *s, char *t) {
    while (*s != '\0') { /* find end of s */
        s++;
    }
    s -= strlen(t);
    while (*s++ == *t++) {
        if (*t == '\0') { /* t is fully matched */
            return 1;
        }
    }
    return 0;
}