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

/* undcl: convert word description to declaraction */
int main() {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token); /* copy token value to out */
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                /* directly put (), [] behind token value */
                strcat(out, token);
            }
            else if (type == '*') {
                /* enclose * + token value in parentheses and store in temp, then copy temp to out */
                sprintf(temp, "(*%s)", out); /* The sprintf() works just like printf() but instead of sending output to console it returns the formatted string. */
                strcpy(out, temp);
            }
            else if (type == NAME) {
                /* put name in front of current output */
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

/*
input: x () * [] * () char
x
x()
(*x())
(*x())[]
(*(*x())[])
(*(*x())[])()
char (*(*x())[])()
*/

int gettoken(void) {
    /* return the type of the next token and write token value to variable token */
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