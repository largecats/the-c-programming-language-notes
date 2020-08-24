/*
Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the line
numbers on which it occurs. Remove noise words like ‘‘the,’’ ‘‘and,’’ and so on.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "../../../helper_functions.h"

#define MAXWORD 100

char *NOISE_WORDS[] = {
    "and",
    "the"
};

int getword(char *word, int *lineNumber, int lim);
struct tnode *addtree(struct tnode *p, char *w, int lineNumber);
void treeprint(struct tnode *p);

int main() {
    struct tnode *root;
    char word[MAXWORD], c;
    int currLineNumber;

    /* add word to tree, skipping strings and comments */
    root = NULL;
    while (getword(word, &currLineNumber, MAXWORD) != EOF) {
        // print_variable(currLineNumber);
        if (isalpha(word[0]) && !string_in_array(word, NOISE_WORDS, sizeof(NOISE_WORDS)/sizeof(char *), 0)) {
            // print_string(word);
            /* if word starts with letter, add it to tree */
            root = addtree(root, word, currLineNumber);
        }
    }
    treeprint(root);
    return 0;
}

/*
$ gcc chapter6/6.5/exercise_6-3/main.c chapter6/6.5/exercise_6-3/getword.c chapter6/6.5/exercise_6-3/llist.c chapter6/6.5/exercise_6-3/tree.c helper_functions.c -o chapter6/6.5/exercise_6-3/result.out

$ chapter6/6.5/exercise_6-3/result.out
wake up, Neo
The Matrix has you
follow the white rabbit
knock knock
Matrix 1
Neo 0
follow 2
has 1
knock 3 3
rabbit 2
up 0
wake 0
white 2
you 1
*/