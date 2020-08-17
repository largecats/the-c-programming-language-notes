/*
Exercise 5-18. Make dcl recover from input errors.
*/

/*
According to https://stackoverflow.com/questions/20170068/kr-c-chapter-5-dcl-issue, the meaning of the exercise is to make dcl continue parsing the expression upon encountering error. There are only two types of error, missing parenthesis and missing (dcl)/name. Both types of error can be handled by ignoring them and proceeding to parse the rest of the expression.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../helper_functions.h"

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

void dcl(void);
void dirdcl(void);
void errmsg(char *);

int gettoken(void);
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last toekn string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char out[1000]; /* output string */
int prevtoken = NO;

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
token =
tokentype = 0
int (*)[13]
token = int
tokentype = 0
token = int
tokentype = (
token = int
tokentype = *
error: expected name or (dcl)
token = int
tokentype = )
token = int
tokentype = )
token = [13]
tokentype = 2
:  pointer to array[13] of int // the missing name is not printed in output, but parsing wasn't affected
token = [13]
tokentype =

$ chapter5/result.out
token =
tokentype = 0
int (*daytab[13]
token = int
tokentype = 0
token = int
tokentype = (
token = int
tokentype = *
token = daytab
tokentype = 0
token = [13]
tokentype = 2
error: missing )
token = [13]
tokentype =

daytab:  array[13] of pointer to int // missing ) does not affect output and is skipped after throwing error
token = [13]
tokentype =
*/

int gettoken(void) {
    /* return next token */
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    print_string(token);
    if (tokentype == NAME || tokentype == PARENS || tokentype == BRACKETS) {
        print_variable(tokentype);
    }
    else {
        print_char(tokentype);
    }
    

    if(prevtoken == YES) /* handle error and move on */
    {
        prevtoken = NO;
        return tokentype;
    }

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

void errmsg(char *msg)
{
    printf("%s",msg);
    prevtoken = YES; /* upon encountering error, set prevtoken to YES */
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
        /* note that the missing parenthesis does not affect parsing dcl */
        if (tokentype != ')') {
            errmsg("error: missing ) \n");
        }
    }
    else if (tokentype == NAME) { /* variable name */
        strcpy(name, token);
    }
    else {
        /* note that missing name/(dcl) does not affect parsing the next token, just that the name won't be printed in the output */
        errmsg("error: expected name or (dcl) \n");
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
