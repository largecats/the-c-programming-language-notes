#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct tnode *talloc(void);
char *strdup1(char *);

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
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup: make a duplicate of s */
char *strdup1 (char *s) {
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL) { /* if there is space */
        strcpy(p, s);
    }
    return p;
}