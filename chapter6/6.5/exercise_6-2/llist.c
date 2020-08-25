#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "../../../helper_functions.h"

struct llist *add_to_llists(struct tnode *treeNode, struct llist *linkedList, int n);
void add_to_llist(struct llist *linkedList, struct tnode *treeNode);
void insert_llist(struct lnode *newNode, struct llist *linkedList);
struct llist *llist_alloc(struct llist *linkedList, struct tnode *treeNode);
struct llist *llist_alloc(struct llist *linkedList, struct tnode *treeNode);
struct lnode *lnode_alloc(struct lnode *linkedNode, struct tnode *treeNode);
void print_llist(struct lnode *head);
void print_llists(struct llist *linkedList);

/* traverse_tree: Traverse tree and add variable names that are identical in the first n characters to the linked lists. */
struct llist *traverse_tree(struct tnode *root, int n) {
    struct tnode *currNode;
    static struct llist *linkedList = NULL; /* points to the root of the tree, preserved across function calls */

    if (root != NULL) {
        // print_string(root->word);
        /* traverse left subtree */
        traverse_tree(root->left, n);

        /* process current node */
        /* find the closest node in the left subtree, i.e., the rightmost child in the left subtree */
        currNode = root->left;
        if (currNode != NULL) {
            while (currNode->right != NULL) {
                currNode = currNode->right;
            }
            if (strlen(currNode->word) >= n && strncmp(currNode->word, root->word, n) == 0) {
                /* if currNode is identical to root in the first n characters, add both to the linked list starting with head */
                linkedList = add_to_llists(root, linkedList, n);
                add_to_llists(currNode, linkedList, n);
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
                linkedList = add_to_llists(root, linkedList, n);
                add_to_llists(currNode, linkedList, n);
            }
        }

        /* traverse right subtree */
        traverse_tree(root->right, n);

        return linkedList;
    }
    else {
        return NULL;
    }
}

/* add_to_llists: add word in treeNode to sorted linked lists. */
// struct llist *add_to_llists(struct tnode *treeNode, struct llist *linkedList, int n) {
//     // void add_to_llist(struct lnode *head, struct tnode *treeNode);
//     void add_to_llist(struct llist *linkedList, struct tnode *treeNode);
//     // print_string(treeNode->word);

//     if (linkedList == NULL) {
//         /* create new linked list in the array of linked list */
//         linkedList = llist_alloc(linkedList, treeNode);
//     }
//     else if (strncmp(treeNode->word, linkedList->head->value, n) == 0) {
//         /* if node word is identical with head of linked list in the first n characters, add it to the linked list. */
//         // add_to_llist(linkedList->head, treeNode);
//         add_to_llist(linkedList, treeNode);
//     }
//     else {
//         /* proceed to check the next linked list */
//         linkedList->next = add_to_llists(treeNode, linkedList->next, n);
//     }
//     return linkedList;
// }

struct llist *add_to_llists(struct tnode *treeNode, struct llist *linkedList, int n) {
    if (linkedList == NULL) {
        /* initialize linked lists */
        linkedList = llist_alloc(linkedList, treeNode);
        return linkedList;
    }
    else {
        if (strncmp(treeNode->word, linkedList->head->value, n) == 0) {
            /* add to existing list */
            add_to_llist(linkedList, treeNode);
            return linkedList;
        }
        /* find where to insert the new list, or add to existing list */
        struct llist *currList = linkedList;
        while (currList->next != NULL && strcmp(treeNode->word, currList->next->head->value) <= 0) {
            /* find the rightmost llist whose head is no greater than treeNode->word; use <= to allow for the equality check below */
            if (strncmp(treeNode->word, currList->next->head->value, n) == 0) {
                /* add to existing list */
                add_to_llist(currList->next, treeNode);
                return linkedList;
            }
            currList = currList->next;
        }
        /* insert new list in proper position */
        if (currList->next != NULL) {
            currList = currList->next;
        }
        struct llist *newList = llist_alloc(newList, treeNode);
        newList->next = currList->next;
        currList->next = newList;
        return linkedList;
    }
}

struct llist *llist_alloc(struct llist *linkedList, struct tnode *treeNode) {
    linkedList = (struct llist *) malloc(sizeof(struct llist));
    if (linkedList != NULL) {
        /* initialize linked list */
        linkedList->next = NULL;
        linkedList->head = lnode_alloc(linkedList->head, treeNode);
    }
    return linkedList;
}

/* add_to_llist: Add word in treeNode to sorted linked list. */
void add_to_llist(struct llist *linkedList, struct tnode *treeNode) {
    struct lnode *newNode = lnode_alloc(newNode, treeNode);
    insert_llist(newNode, linkedList);
}

/* insert_llist: insert newNode into sorted linked list */
// void insert_llist(struct lnode *newNode, struct llist *linkedList) {
//     struct lnode *currNode = linkedList->head;
    
//     if (strcmp(newNode->value, currNode->value) == 0) {
//         /* word is already in linked list */
//         return ;
//     }
//     while (currNode->next != NULL) {
//         if (strcmp(newNode->value, currNode->value) == 0) {
//             /* word is already in linked list */
//             return ;
//         }
//         currNode = currNode->next;
//     }
//     /* if word is not in the linked list yet, create new linked node from treeNode*/
//     currNode->next = newNode;
    
// }

void insert_llist(struct lnode *newNode, struct llist *linkedList) {
    struct lnode *currNode = linkedList->head;
    // print_string(newNode->value);
    // print_llist(linkedList->head);

    if (currNode == NULL || strcmp(newNode->value, currNode->value) <= 0) {
        if (strcmp(newNode->value, currNode->value) == 0) {
            /* word is already in linked list */
            return;
        }
        /* if head is null or newNode->value is less than head->value, insert in front of current head */
        newNode->next = linkedList->head;
        linkedList->head = newNode;
    }
    else {
        /* else, insert in proper position */
        while (currNode->next != NULL && strcmp(newNode->value, currNode->next->value) <= 0) {
            /* find the rightmost node whose value is no greater than newNode->value; use <= to allow for the equality check below */
            if (strcmp(newNode->value, currNode->next->value) == 0) {
                /* word is already in linked list */
                return;
            }
            currNode = currNode->next;
        }
        if (currNode->next != NULL) {
            /* because we used <= instead of < in the while loop, need to check currNode->next separately again */
            currNode = currNode->next;
        }
        newNode->next = currNode->next;
        currNode->next = newNode;
    }
}

/* lnode_alloc: create a linked node from treeNode */
struct lnode *lnode_alloc(struct lnode *linkedNode, struct tnode *treeNode) {
    linkedNode = (struct lnode *) malloc(sizeof(struct lnode));
    if (linkedNode != NULL) {
        linkedNode->value = treeNode->word;
        linkedNode->next = NULL;
    }
    return linkedNode;
}

/* print_llists: print linked lists */
void print_llists(struct llist *linkedList) {
    if (linkedList == NULL) {
        return;
    }
    while (linkedList != NULL) {
        // printf("%s", "printing linked list\n");
        print_llist(linkedList->head);
        linkedList = linkedList->next;
    }
    putchar('\n');
}

/* print_llist: print linked list starting from head */
void print_llist(struct lnode *head) {
    struct lnode *currNode = head;
    while (currNode != NULL) {
        printf("%s ", currNode->value);
        currNode = currNode->next;
    }
    putchar('\n');
}