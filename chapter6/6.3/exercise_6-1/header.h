#include <stdio.h>

#define MAXWORD 100 /* maximum length of a word */

/* https://stackoverflow.com/questions/228684/how-to-declare-a-structure-in-a-header-that-is-to-be-used-by-multiple-files-in-c#228691 */
/* define struct in header file */
struct key {
    char *word;
    int count;
};
/* declare variable of type struct key as extern and define it in mian.c*/
extern struct key keytab[];