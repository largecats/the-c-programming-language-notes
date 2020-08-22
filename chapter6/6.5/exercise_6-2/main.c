/* 
Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each group of variable names that are
identical in the first 6 characters, but different somewhere thereafter. Don’t count words within strings and comments. Make
6 a parameter that can be set from the command line. 
*/

#include <stdio.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void print_similar_variables(struct tnode *, int n);
int getword(char *, int);

/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD], c;
    int n;

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

    /* print similar variable names */
    print_similar_variables(root, n);
    return 0;
}

/*
$ gcc chapter6/6.5/exercise_6-2/main.c  helper_functions.c -o chapter6/6.5/exercise_6-2/result.out

$ chapter6/6.5/exercise_6-2/result.out
*/