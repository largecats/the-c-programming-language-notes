#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "../../../helper_functions.h"

/* hash: compute hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;
    
    /* lok for s in the chain with hash value = hash(s) */
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np; /* found */
        }
        return NULL; /* not found */
    }
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    /* add name */
    if ((np = lookup(name)) == NULL) {
        /* name does not exist in hashtab */
        np = (struct nlist *) malloc(sizeof(*np)); /* create new block in linked list*/
        if (np == NULL || (np->name = strdup1(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name); /* hash value of name */
        /* insert np before the first block in the chain pointed to by pointers in hashtab */
        np->next = hashtab[hashval]; /* put np before the block currently pointed to by hashtab[hashval] */
        hashtab[hashval] = np; /* let hashtab[hashval] point to np */
    }
    else {
        /* name exists in hashtab */
        free((void *) np->defn); /* free up previous defn */
    }
    /* add defn */
    if ((np->defn = strdup1(defn)) == NULL) {
        return NULL;
    }
    return np;
}

/* undef: remove a name and definition from hashtab. */
void undef(char *name) {
    unsigned hashval = hash(name);
    struct nlist *head = hashtab[hashval];
    if (strcmp(name, head->name) == 0) {
        /* unlink found block */
        hashtab[hashval] = head->next; /* head = head->next will raise segmentation fault */
        free((void *) head->name);
        free((void *) head->defn);
    }
    else {
        struct nlist *np = hashtab[hash(name)];
        /* lok for s in the chain with hash value = hash(s) */
        for (; np->next != NULL; np = np->next) {
            if (strcmp(name, np->next->name) == 0) {
                /* unlink found block */
                np->next = np->next->next;
                free((void *) np->next->name);
                free((void *) np->next->defn);
            }
        }
    }
    
}