#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../../helper_functions.h"

#define MAXWORD 100 /* maximum length of a word */

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

int getword(char *, int);
int binsearch(char *, struct key *, int);

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
$ gcc chapter6/6.3/count_keyword.c helper_functions.c -o chapter6/6.3/result.out

$ chapter6/6.3/result.out
int i = 0;
int j = 0;
printf("i=%d", i);
   2 int
   1 printf
*/

/* binsearch: find word in tab[0] ... tab[n-1] and return its index in tab if found */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        }
        else if (cond > 0) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1; /* if not found */
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word; /* pointer to pointer to char, i.e., pointer to string */

    while (isspace(c = getch())) {
        ; /* skip spaces */
    }
    /* check the first non-space characer */
    if (c != EOF) {
        /* if the first non-space character is not EOF, store in *w */
        *w++ = c;
    }
    if (!isalpha(c)) {
        /* if the first non-space character is not a letter, terminate and return it */
        *w = '\0';
        return c;
    }
    /* continue reading the renamining characters in the word until meeting a character that is not a letter or number, which means that the word has ended */
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w); /* put it back */
            break; /* exit the for loop */
        }
    }
    *w = '\0';
    return word[0];
}