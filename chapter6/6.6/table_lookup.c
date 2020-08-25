#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../helper_functions.h"

struct nlist {
    /* struct for table entry */
    struct nlist *next; /* next entry in the chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *s);
struct nlist *lookup(char *s);
char *strdup1(char *);
struct nlist *install(char *name, char *defn);
void print_hashtab(struct nlist *hashtab[]);

int main() {
    install("MAXLEN", "100");
    install("IN", "1");
    print_hashtab(hashtab);
}

/*
$ gcc chapter6/6.6/table_lookup.c helper_functions.c -o chapter6/6.6/result.out

$ chapter6/6.6/result.out
*/

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

char *strdup1(char *);

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

/* strdup: make a duplicate of s */
char *strdup1 (char *s) {
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL) { /* if there is space */
        strcpy(p, s);
    }
    return p;
}

/* print_hashtab: print all (name, defn) entries in hashtab */
void print_hashtab(struct nlist *hashtab[]) {
    for (int i=0; i < HASHSIZE; i++) {
        for (struct nlist *np = hashtab[i]; np != NULL; np = np->next) {
            print_string(np->name);
            print_string(np->defn);
        }
    }
}