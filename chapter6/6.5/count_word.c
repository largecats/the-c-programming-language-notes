#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            /* if word starts with letter, add it to tree */
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

/*
$ gcc chapter6/6.5/count_word.c chapter6/6.5/getword.c chapter6/6.5/tree.c helper_functions.c -o chapter6/6.5/result.out

$ chapter6/6.5/result.out
hello Neo knock knock follow the white rabbit
   1 Neo
   1 follow
   1 hello
   2 knock
   1 rabbit
   1 the
   1 white
*/