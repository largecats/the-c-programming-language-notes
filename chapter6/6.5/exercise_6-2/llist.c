#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "../../../helper_functions.h"

struct lnode *lalloc(struct lnode *linkedNode, struct tnode *treeNode);

/* add_to_llists: Traverse tree and add variable names that are identical in the first n characters to the linked lists. */
struct llist *add_to_llists(struct tnode *root, int n) {
    struct llist *add_to_llists_helper(struct tnode *treeNode, struct llist *linkedList, int n);

    if (root != NULL) {
        struct tnode *currNode;
        static struct llist *linkedList = NULL; /* points to the root of the tree */

        /* traverse left subtree */
        add_to_llists(root->left, n);

        /* process current node */
        /* find the closest node in the left subtree, i.e., the rightmost child in the left subtree */
        currNode = root->left;
        if (currNode != NULL) {
            while (currNode->right != NULL) {
                currNode = currNode->right;
            }
            if (strlen(currNode->word) >= n && strncmp(currNode->word, root->word, n) == 0) {
                /* if currNode is identical to root in the first n characters, add both to the linked list starting with head */
                linkedList = add_to_llists_helper(root, linkedList, n);
                add_to_llists_helper(currNode, linkedList, n);
            }
        }
        /* find the closest node in the right subtree, i.e., the leftmost child in the right subtree */
        currNode = root->right;
        if (currNode != NULL) {
            while (currNode->left != NULL) {
                currNode = currNode->left;
            }
            if (strlen(currNode->word) >= n && strncmp(currNode->word, root->word, n) == 0) {
                /* if currNode is identical to root in the first n characters, add both to the linked list starting with head */
                linkedList = add_to_llists_helper(root, linkedList, n);
                add_to_llists_helper(currNode, linkedList, n);
            }
        }

        /* traverse right subtree */
        add_to_llists(root->right, n);

        return linkedList;
    }
    else {
        return NULL;
    }
}

/* add_to_llists_helper: add word in treeNode to the linked lists. */
struct llist *add_to_llists_helper(struct tnode *treeNode, struct llist *linkedList, int n) {
    void add_to_llist(struct lnode *head, struct tnode *treeNode);

    if (linkedList == NULL) {
        /* create new linked list in the array of linked list */
        linkedList = (struct llist *) malloc(sizeof(struct llist));
        linkedList->next = NULL;
        linkedList->head = lalloc(linkedList->head, treeNode);
    }
    else if (strncmp(treeNode->word, linkedList->head->value, n) == 0) {
        /* if node word is identical with head of linked list, add it to the linked list. */
        add_to_llist(linkedList->head, treeNode);
    }
    else {
        /* proceed to check the next linked list */
        linkedList->next = add_to_llists_helper(treeNode, linkedList->next, n);
    }
    return linkedList;
}

/* add_to_llist: Add word in treeNode to linked list. */
void add_to_llist(struct lnode *head, struct tnode *treeNode) {
    struct lnode *currNode = head;
    while (currNode->next != NULL) {
        if (strcmp(currNode->value, treeNode->word)) {
            /* word is already in linked list */
            return;
        }
        currNode = currNode->next;
    }
    /* if word is not in the linked list yet, create new linked node from treeNode*/
    currNode->next = lalloc(currNode->next, treeNode);
}

/* lalloc: create a linked node from treeNode */
struct lnode *lalloc(struct lnode *linkedNode, struct tnode *treeNode) {
    linkedNode = (struct lnode *) malloc(sizeof(struct lnode));
    if (linkedNode != NULL) {
        linkedNode->value = treeNode->word;
        linkedNode->next = NULL;
    }
    return linkedNode;
}

/* print_llists: print linked lists */
void print_llists(struct llist *linkedList) {
    void print_llist(struct lnode *head);

    if (linkedList == NULL) {
        return;
    }
    while (linkedList != NULL) {
        print_llist(linkedList->head);
        putchar('\n');
        linkedList = linkedList->next;
    }
}

/* print_llist: print linked list starting from head */
void print_llist(struct lnode *head) {
    struct lnode *currNode = head;
    while (currNode != NULL) {
        printf("%s ", currNode->value);
        currNode = currNode->next;
    }
}