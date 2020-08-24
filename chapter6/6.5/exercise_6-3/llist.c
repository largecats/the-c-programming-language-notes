#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "../../../helper_functions.h"

/* append_to_llist: append newNode to the linked list starting with head */
void append_to_llist(struct lnode *newNode, struct lnode *head) {
    struct lnode *currNode = head;
    while (currNode->next != NULL) {
        currNode = currNode->next;
    }
    currNode->next = newNode;
}

/* lnode_alloc: create a linked node from treeNode */
struct lnode *lnode_alloc(int value) {
    struct lnode *linkedNode = (struct lnode *) malloc(sizeof(struct lnode));
    if (linkedNode != NULL) {
        linkedNode->value = value;
        linkedNode->next = NULL;
    }
    return linkedNode;
}

/* print_llist: print linked list starting from head */
void print_llist(struct lnode *head) {
    struct lnode *currNode = head;
    while (currNode != NULL) {
        printf("%d ", currNode->value);
        currNode = currNode->next;
    }
    putchar('\n');
}