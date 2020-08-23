#include <stdio.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* struct for node in linked list */
struct lnode {
    char *value;
    struct lnode *next;
};
/* 
E.g., ... -> aaa12 -> aaa23 -> aaa34 -> ...
*/

/* struct for linked list */
struct llist {
    struct lnode *head;
    struct llist *next;
};
/*
E.g.,
head1 -> aaa12 -> aaa23 -> aaa34 -> ...
|
head2 -> bbb23 -> bbb34 -> ...
|
head3 -> ccc -> ...
|
...
*/