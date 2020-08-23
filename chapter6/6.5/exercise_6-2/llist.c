#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

/* add_to_llists: Traverse tree and add variable names that are identical in the first n characters to the array of linked lists. */
void add_to_llistArr(struct tnode *root, struct lnode *head, int n) {
    if (*root != NULL) {
        char *currWord = root->word;
        /* traverse left subtree */
        add_to_llistArr(root->left, *head, n);

        /* add current node */

        /* traverse right subtree */
        add_to_llistArr(root->right, *head, n);
    }
}

/* print_llists: print each node in the array of linked lists. */
void print_llistArrr(struct lnode *head) {
    while (*head++ != NULL) {
        /* print each linked list in the array */
        struct lnode currHead = *head;
        while (currHead.next != NULL) {
            printf("%s", currHead.value);
            currHead = currHead.next;
        }
    }
}

