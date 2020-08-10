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
        print_char_with_visible_blanks(tokentype);
        if (tokentype != '\n') {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

int gettoken(void) {
    /* return next topken */
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t') {
        ; /* skip blanks and tabs */
    }
    if (c == '(') {
        /* peek at the next character */
        if ((c = getch()) == ')') { /* if the next character is closing paren */
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c); /* put back the next character to input buffer*/
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; ) {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        /* name starts with letter and may contain numbers */
        for (*p++ = c; isalnum(c = getch());) {
            *p++ = c;
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

    for (ns = 0; gettoken() == '*'; ) /* count *'s */ {
        ns++;
    }
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
        }
        else if (tokentype == NAME) { /* variable name */
            strcpy(name, token);
        }
        else {
            printf("error: expected name or (dcl)\n");
        }
        while ((type=gettoken()) == PARENS || type == BRACKETS) {
            if (type == PARENS) {
                strcat(out, " function returning");
            }
            else {
                strcat(out, " array");
                strcat(out, token);
                strcat(out, " of");
            }
        }
    }
}