#include <stdio.h>

extern char *NOISE_WORDS[];

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* struct for node in linked list */
struct lnode {
    char *value;
    int count;
    struct lnode *next;
};
/* 
E.g., ... -> 11 -> 20 -> ...
*/

/* struct for linked list */
struct llist {
    struct lnode *head;
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