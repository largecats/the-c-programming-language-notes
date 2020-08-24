#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../../helper_functions.h"
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
struct key *binsearch(char *, struct key *, int);

/* count C keywords: pointer version */
int main() {
    char word[MAXWORD];
    struct key *p;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((p=binsearch(word, keytab, NKEYS)) != NULL) {
                p->count++; /* increments (*p).count */
            }
        }
    }
    for (p = keytab; p < keytab + NKEYS; p++) {
        if (p->count > 0) {
            printf("%4d %s\n", p->count, p->word);
        }
    }
    return 0;
}

/*
$ gcc chapter6/6.4/count_keyword_pointer_version.c chapter6/6.4/getword.c chapter6/6.4/search.c helper_functions.c -o chapter6/6.4/result.out

$ chapter6/6.4/result.out
int i = 0;
int j = 0;
printf("i=%d", i);
   2 int
   1 printf
*/