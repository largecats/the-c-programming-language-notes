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

struct tnode *addtree(struct tnode *, char *);
struct llist * add_to_llists(struct tnode *, int);
void print_llists(struct llist *);
int getword(char *, int);
void treeprint(struct tnode *p);

/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    struct llist *identical_in_n; /* linked lists that store words that are identical in the first n charaters */
    char word[MAXWORD], c;
    int n = N;

    /* add word to tree, skipping strings and comments */
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            /* if word starts with letter, add it to tree */
            root = addtree(root, word);
        }
    }

    /* get n from command line */
    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'n':
                    n = atoi(c);
                    break;
            }
        }
    }

    // print_variable(n);

    identical_in_n = NULL;
    /* scan tree with root and add variable names that are identical in the first n characters the linked list of linked lists */
    identical_in_n = add_to_llists(root, n);
    treeprint(root);
    /* print the linked lists */
    print_llists(identical_in_n);
    return 0;
}

/*
$ gcc chapter6/6.5/exercise_6-2/main.c chapter6/6.5/exercise_6-2/getword.c chapter6/6.5/exercise_6-2/llist.c chapter6/6.5/exercise_6-2/tree.c helper_functions.c -o chapter6/6.5/exercise_6-2/result.out

$ chapter6/6.5/exercise_6-2/result.out
*/