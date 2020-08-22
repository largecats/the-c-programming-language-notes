/*
Exercise 6-1. Our version of getword does not properly handle underscores, string constants, comments, or preprocessor
control lines. Write a better version.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "header.h"

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"extern", 0},
    {"float", 0},
    {"int", 0},
    {"printf", 0},
    {"signed", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

/* #define NKEYS (sizeof keytab / sizeof(struct key)) */
#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main() {
    int n;
    char word[MAXWORD]; /* to store the read words */

    while (getword(word, MAXWORD) != EOF) {
        print_string(word);
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
#define MAXLEN 10
word = #
int i = 0; / * int * /
word = int
word = i
word = =
word = 0
word = /
int i_1 = 1;
word = int
word = i
word = _ # note that the 1 following _ is skipped
word = =
word = 1
printf("i=%d", i); / * printf * /
word = printf
word = (
word = i
word = )
word = /
   2 int
   1 printf
*/
