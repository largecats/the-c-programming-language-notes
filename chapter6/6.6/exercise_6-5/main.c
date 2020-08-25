/*
Exercise 6-5. Write a function undef that will remove a name and definition from the table maintained by lookup and
install.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "../../../helper_functions.h"

struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *s);
struct nlist *lookup(char *s);
char *strdup1(char *);
struct nlist *install(char *name, char *defn);
void undef(char *name);

int main() {
    install("MAXLEN", "100");
    install("IN", "1");
    print_nlist(hashtab);
    undef("IN");
    print_nlist(hashtab);
}

/*
$ gcc chapter6/6.6/exercise_6-5/main.c chapter6/6.6/exercise_6-5/hashtab.c chapter6/6.6/exercise_6-5/nlist.c helper_functions.c -o chapter6/6.6/exercise_6-5/result.out

$ chapter6/6.6/exercise_6-5/result.out
#define IN 1
#define MAXLEN 100

#define MAXLEN 100

*/