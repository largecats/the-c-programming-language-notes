/*
Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
*/

#include <stdio.h>
#include "../../../helper_functions.h"

/*
char *strcpy(s,ct) copy string ct to string s, including ’\0’; return s.
char *strncpy(s,ct,n) copy at most n characters of string ct to s; return s. Pad with ’\0’’s if ct
has fewer than n characters.

char *strcat(s,ct) concatenate string ct to end of string s; return s.
char *strncat(s,ct,n) concatenate at most n characters of string ct to string s, terminate s with
’\0’; return s.

int strcmp(cs,ct) compare string cs to string ct, return <0 if cs<ct, 0 if cs==ct, or >0 if
cs>ct.
int strncmp(cs,ct,n) compare at most n characters of string cs to string ct; return <0 if cs<ct, 0
if cs==ct, or >0 if cs>ct.
*/

char *strncpy1(char *s, char *t, int n);
char *strncat1(char *s, char *t, int n);
int strncmp1(char *s, char *t, int n);

int main() {
    char s[MAXLINE] = "hello ";
    char t[] = "Neo";

    strncpy1(s, t, 3); /* copy the first 3 characters in "Neo" to "hello" */
    print_string(s); /* "Neolo */
    strncat1(s, t, 3); /* concat the first 3 characters in "Neo" to "Neolo" */
    print_string(s);
    printf("%d\n", strncmp1(s, t, 3)); /* compare the first 3 characters in "Neolo" with "Neo" */
}

/*
$ gcc chapter5/5.5/exercise_5-5/main.c helper_functions.c -o chapter5/5.5/exercise_5-5/result.out

$ chapter5/5.5/exercise_5-5/result.out
s = Neolo
s = Neolo Neo
0
*/

char *strncpy1(char *s, char *t, int n) {
    while (n > 0 && *t != '\0') {
        *s++ = *t++;
        n--;
    }
    if (n > 0) {
        for (; n > 0; n--) {
            *s++ = '\0';
        }
    }
    return s;
}

char *strncat1(char *s, char *t, int n) {
    while (*s++ != '\0') { /* find end of s */
        ;
    }
    *s--;
    while (n > 0 && *t != '\0') {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
    return s;
}

int strncmp1(char *s, char *t, int n) {
    for (; n > 0 && *s == *t; *s++, *t++, n--) {
        if (*s == '\0') {
            return 0;
        }
    }
    if (n == 0) {
        return 0;
    }
    else {
        return *s - *t;
    }
}
