#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "../../../helper_functions.h"

struct tnode *talloc(void);

/* addtree: add a node with word=w, at or below the tree node pointed to by p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) { /* word not in tree */
        p = talloc(); /* make a new node */
        p->word = strdup1(w);
        p->count = 1;
        p->left = p->right = NULL; /* initialize left, right children */
    }
    else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++; /* word already in tree, increment count */
    }
    else if (cond < 0) {
        p->left = addtree(p->left, w); /* add node to left subtree of p */
    }
    else {
        p->right = addtree(p->right, w); /* add node to right subtree of p */
    }
    return p;
}

/* treeprint: in-order, depth first traversal of tree p https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/ */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
    return (struct node *) malloc(sizeof(struct tnode));
}