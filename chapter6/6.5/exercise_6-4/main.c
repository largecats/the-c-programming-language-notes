/*
Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing order of frequency of
occurrence. Precede each word by its count.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "../../../helper_functions.h"

#define MAXWORD 100

int getword(char *word, int lim);
struct llist *traverse_tree(struct tnode *root);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
void print_llist(struct llist *linkedList);

int main() {
    struct tnode *root;
    char word[MAXWORD];
    struct llist *linkedList;

    /* add word to tree, skipping strings and comments */
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            // print_string(word);
            /* if word starts with letter, add it to tree */
            root = addtree(root, word);
        }
    }
    // treeprint(root);
    linkedList = traverse_tree(root);
    print_llist(linkedList);
    return 0;
}

/*
$ gcc chapter6/6.5/exercise_6-4/main.c chapter6/6.5/exercise_6-4/getword.c chapter6/6.5/exercise_6-4/llist.c chapter6/6.5/exercise_6-4/tree.c helper_functions.c -o chapter6/6.5/exercise_6-4/result.out

$ chapter6/6.5/exercise_6-4/result.out
hello Neo
knock a a a knock a a
   5 a
   2 knock
   1 hello
   1 Neo
*/