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
}
/* 
E.g., ... -> aaa12 -> aaa23 -> aaa34 -> ...
*/