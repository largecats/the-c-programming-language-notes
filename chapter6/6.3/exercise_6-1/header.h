#include <stdio.h>

#define MAXWORD 100 /* maximum length of a word */

struct key;
struct key keytab[];

int getword(char *, int);
int binsearch(char *, struct key *, int);