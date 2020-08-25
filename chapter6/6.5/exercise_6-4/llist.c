#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "../../../helper_functions.h"

struct llist *llist_alloc(struct llist *linkedList, struct tnode *treeNode);
struct llist *add_to_llist(struct llist *linkedList, struct tnode *treeNode);
struct lnode *lnode_alloc(struct lnode *linkedNode, struct tnode *treeNode);
void insert_llist(struct lnode *newNode, struct llist *linkedList);
void print_llist(struct llist *linkedList);

/* traverse_tree: Traverse tree and add variable names that are identical in the first n characters to the linked lists. */
struct llist *traverse_tree(struct tnode *root) {
    struct tnode *currNode;
    static struct llist *linkedList = NULL; /* points to the root of the tree, preserved across function calls */

    if (root != NULL) {
        // print_string(root->word);
        /* traverse left subtree */
        traverse_tree(root->left);

        /* process current node */
        // print_string(root->word);
        if (linkedList == NULL) {
            /* initialize linked list */
            linkedList = llist_alloc(linkedList, root);
        }
        else {
            linkedList = add_to_llist(linkedList, root);
        }

        /* traverse right subtree */
        traverse_tree(root->right);
    
        // print_llist(linkedList);
        return linkedList;
    }
    else {
        return NULL;
    }
}

struct llist *llist_alloc(struct llist *linkedList, struct tnode *treeNode) {
    linkedList = (struct llist *) malloc(sizeof(struct llist));
    if (linkedList != NULL) {
        /* initialize linked list */
        linkedList->head = lnode_alloc(linkedList->head, treeNode);
    }
    return linkedList;
}

/* add_to_llist: Add word in treeNode to sorted linked list. */
struct llist *add_to_llist(struct llist *linkedList, struct tnode *treeNode) {
    struct lnode *newNode = lnode_alloc(newNode, treeNode);
    insert_llist(newNode, linkedList);
    return linkedList;
}

/* insert_llist: insert newNode into sorted linkedList */
void insert_llist(struct lnode *newNode, struct llist *linkedList) {
    struct lnode *currNode = linkedList->head;

    if (currNode == NULL || newNode->count >= currNode->count) {
        /* if head is null or newNode->count is no less than head->count, insert in front of current head */
        newNode->next = linkedList->head;
        linkedList->head = newNode;
    }
    else {
        /* else, insert in proper position */
        struct lnode *prevNode = currNode;
        while (currNode->next != NULL && newNode->count <= currNode->count) {
            // /* find the rightmost node whose count is no less than newNode->count */
            prevNode = currNode;
            currNode = currNode->next;
        }
        currNode = prevNode;
        newNode->next = currNode->next;
        currNode->next = newNode;
    }
}

/* lnode_alloc: create a linked node from treeNode */
struct lnode *lnode_alloc(struct lnode *linkedNode, struct tnode *treeNode) {
    linkedNode = (struct lnode *) malloc(sizeof(struct lnode));
    if (linkedNode != NULL) {
        linkedNode->value = treeNode->word;
        linkedNode->count = treeNode->count;
        linkedNode->next = NULL;
    }
    return linkedNode;
}

/* print_llist: print linked list starting from head */
void print_llist(struct llist *linkedList) {
    struct lnode *currNode = linkedList->head;
    while (currNode != NULL) {
        printf("%4d %s\n", currNode->count, currNode->value);
        currNode = currNode->next;
    }
}