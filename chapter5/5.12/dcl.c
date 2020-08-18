#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../helper_functions.h"

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last toekn string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char out[1000]; /* output string */

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
$ chapter5/result.out
char **argv
argv:  pointer to pointer to char
int (*daytab)[13]
daytab:  pointer to array[13] of int
int *daytab[13]
daytab:  array[13] of pointer to int
void *comp()
comp:  function returning pointer to void
void (*comp)()
comp:  pointer to function returning void
char (*(*x())[])()
x:  function returning pointer to array[] of pointer to function returning char
char (*(*x[3])())[5]
x:  array[3] of pointer to function returning pointer to array[5] of char
*/

int gettoken(void) {
    /* return next token */
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t') {
        ; /* skip blanks and tabs */
    }
    if (c == '(') {
        /* peek at the next character */
        if ((c = getch()) == ')') { /* if the next character is closing paren */
            strcpy(token, "()"); /* store token '()' in variable token */
            return tokentype = PARENS;
        }
        else {
            ungetch(c); /* put back the next character to input buffer*/
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; ) {
            ; /* read characters enclosed by [] */
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        /* name starts with letter and may contain numbers */
        for (*p++ = c; isalnum(c = getch());) {
            *p++ = c; /* read name */
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

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
            printf("error: missing )\n");
        }
    }
    else if (tokentype == NAME) { /* variable name */
        strcpy(name, token);
    }
    else {
        printf("error: expected name or (dcl)\n");
    }
    /* The following tokens after the first one must be () or [] */
    while ((type=gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            /* token of the form xxx() must be a function */
            strcat(out, " function returning");
        }
        else {
            /* token of the form xxx[] must be an array */
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
