/*
Exercise 5-20. Expand dcl to handle declarations with function argument types, qualifiers like const, and so on.
*/

/* http://www.learntosolveit.com/cprogramming/Ex_5.20_dcl-funcargs.html */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "extern.h"

#define MAXTOKEN 100

enum {NAME,PARENS,BRACKETS};
enum {NO,YES};

void dcl(void);
void dirdcl(void);
void errmsg(char *);
int gettoken(void);

int tokentype;   /* type of last token */
char token[];    /* last token string */
char name[]; /* identifier name */
char datatype[]; /* data type = char,int, etc */
char out[];
int prevtoken;

int main() {
    /* convert declaration to words */
    while (gettoken() != EOF) {
        strcpy(datatype, token); /* 1st token on line is the data type */
        out[0] = '\0';
        dcl(); /* parse rest of line */
        if (tokentype != '\n') {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/*
gcc chapter5/5.12/exercise_5-20/main.c chapter5/5.12/exercise_5-20/parmdcl.c chapter5/5.12/exercise_5-20/gettoken.c helper_functions.c -o chapter5/5.12/exercise_5-20/result.out
$ chapter5/5.12/exercise_5-20/result.out
token =
tokentype = 0
int compare(char **s, char **t)
token = int
tokentype = 0
token = compare
tokentype = 0
token = compare
tokentype = (
token = char
tokentype = 0
token = char
tokentype = *
token = char
tokentype = *
token = char
tokentype = *
token = s
tokentype = 0
token = s
tokentype = ,
token = char
tokentype = 0
token = char
tokentype = *
token = char
tokentype = *
token = char
tokentype = *
token = t
tokentype = 0
token = t
tokentype = )
t: function expecting pointer to pointer to char, pointer to pointer to char and returning int
token = t
tokentype =
*/

/* dcl: parse a declaractor */
void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; ) /* count *s */ {
        ns++;
    }
    dirdcl(); /* parse direct dcl, which is without *s */ 
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
    int type;

    /* 
    By definition, a direct dcl must begin with an identifier name or parenthesis, e.g., name, name[], (dcl), name().
    */
    if (tokentype == '(') {
        dcl(); /* parse the dcl contained within parentheses */
        if (tokentype != ')') {
            errmsg("error: missing ) \n");
        }
    }
    else if (tokentype == NAME) { /* variable name */
        strcpy(name, token);
    }
    else {
        errmsg("error: expected name or (dcl)\n");
    }
    /* The following tokens after the first one must be () or [] */
    while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(') {
        if (type == PARENS) {
            /* token of the form xxx() must be a function */
            strcat(out, " function returning");
        }
        else if (type == '(') {
            strcat(out, "function expecting");
            parmdcl(); /* parse function parameters */
            strcat(out, " and returning");
        }
        else {
            /* token of the form xxx[] must be an array */
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

/* errmsg: print error message and indicate avail. token */
void errmsg(char *msg)
{
    printf("%s",msg);
    prevtoken = YES;
}

