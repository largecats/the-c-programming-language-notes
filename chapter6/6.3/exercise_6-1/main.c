/*
Exercise 6-1. Our version of getword does not properly handle underscores, string constants, comments, or preprocessor
control lines. Write a better version.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../../helper_functions.h"
#include "header.h"

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    /* ... */
    {"int", 0},
    {"printf", 0},
    /* ... */
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

/* #define NKEYS (sizeof keytab / sizeof(struct key)) */
#define NKEYS (sizeof keytab / sizeof keytab[0])

/* count C keywords */
int main() {
    int n;
    char word[MAXWORD]; /* to store the read words */

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                /* if word is in keytab, increment its count */
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

/*
$ gcc chapter6/6.3/exercise_6-1/main.c chapter6/6.3/exercise_6-1/search.c chapter6/6.3/exercise_6-1/getword.c helper_functions.c -o chapter6/6.3/exercise_6-1/result.out

$ chapter6/6.3/exercise_6-1/result.out
int i = 0;
int j = 0;
printf("i=%d", i);
   2 int
   1 printf
*/
