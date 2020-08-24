#include <stdio.h>

extern char *NOISE_WORDS[];

struct tnode {
    char *word;
    int count;
    struct lnode *lineNumbers;
    struct tnode *left;
    struct tnode *right;
};

/* struct for node in linked list */
struct lnode {
    int value;
    struct lnode *next;
};
/* 
E.g., ... -> 11 -> 20 -> ...
*/

void append_to_llist(struct lnode *newNode, struct lnode *head);
struct lnode *lnode_alloc(int value);
void print_llist(struct lnode *head);