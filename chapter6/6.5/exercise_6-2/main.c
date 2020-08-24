/* 
Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each group of variable names that are
identical in the first 6 characters, but different somewhere thereafter. Don’t count words within strings and comments. Make
6 a parameter that can be set from the command line. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
#include "../../../helper_functions.h"

#define MAXWORD 100
#define N 6

void parse_args(int argc, char *argv[], int *np);
struct tnode *addtree(struct tnode *, char *);
struct llist * traverse_tree(struct tnode *, int);
void print_llists(struct llist *);
int getword(char *, int);
void treeprint(struct tnode *p);

/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    struct llist *identical_in_n; /* linked lists that store words that are identical in the first n charaters */
    char word[MAXWORD], c;
    int n = N;

    /* parse command line argument */
    parse_args(argc, argv, &n);
    print_variable(n);

    /* add word to tree, skipping strings and comments */
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            /* if word starts with letter, add it to tree */
            root = addtree(root, word);
        }
    }

    identical_in_n = NULL;
    /* scan tree with root and add variable names that are identical in the first n characters the linked list of linked lists */
    identical_in_n = traverse_tree(root, n);
    treeprint(root);
    /* print the linked lists */
    print_llists(identical_in_n);
    return 0;
}

/*
$ gcc chapter6/6.5/exercise_6-2/main.c chapter6/6.5/exercise_6-2/parse_args.c chapter6/6.5/exercise_6-2/getword.c chapter6/6.5/exercise_6-2/llist.c chapter6/6.5/exercise_6-2/tree.c helper_functions.c -o chapter6/6.5/exercise_6-2/result.out

$ chapter6/6.5/exercise_6-2/result.out -n 3
n = 3
ccc12 aaa23 aaa34 aaa12 ccc aaa12
   2 aaa12
   1 aaa23
   1 aaa34
   1 ccc
   1 ccc12
aaa12 aaa23 aaa34
ccc ccc12
*/