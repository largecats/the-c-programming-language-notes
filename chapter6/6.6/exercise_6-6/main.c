/*
Exercise 6-6. Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs,
based on the routines of this section. You may also find getch and ungetch helpful.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "header.h"

#define MAXWORD 100

int getword(char *word, int lim);
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
void print_nlist(struct nlist *hashtab[]);

struct nlist *hashtab[HASHSIZE]; /* pointer table */

int main() {
    char word[MAXWORD], name[MAXWORD], defn[MAXWORD];
    struct nlist *result;

    while (getword(word, MAXWORD) != EOF) {
        if (isalnum(word[0]) || word[0] == '#') {
            if (strcmp(word, "#define") == 0) {
                getword(name, MAXWORD);
                getword(defn, MAXWORD);
                install(name, defn);
            }
            else {
                result = lookup(name);
                print_string(result->defn);
            }
        }
    }
    print_nlist(hashtab);
    return 0;
}

/*
$ gcc chapter6/6.6/exercise_6-6/main.c chapter6/6.6/exercise_6-6/getword.c chapter6/6.6/exercise_6-6/hashtab.c chapter6/6.6/exercise_6-6/nlist.c helper_functions.c -o chapter6/6.6/exercise_6-6/result.out

$ chapter6/6.6/exercise_6-6/result.out
#define MAXLEN 10
result->defn = 10
#define MAXWORD 100
result->defn = 100
name = MAXLEN, defn = 10
name = MAXWORD, defn = 100
*/