/*
Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations.
*/

/*
http://www.learntosolveit.com/cprogramming/Ex_5.19_undcl.html
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

int gettoken(void);
int nexttoken(void);
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last toekn string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char out[1000]; /* output string */
int prevtoken = NO;

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
                /* peek at the next token to see if need to add parentheses */
                if ((type = nexttoken()) == PARENS || type == BRACKETS) {
                    sprintf(temp, "(*%s)", out);
                }
                else {
                    sprintf(temp, "*%s", out);
                }
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
Before:
$ chapter5/result.out
argv * * char
char (*(*argv))

After:
$ chapter5/result.out
argv * * char
char **argv
*/

/* nexttoken: get the next token and push it back */
int nexttoken(void) {
    int type;

    type = gettoken();
    prevtoken = YES;
    return type;
}

int gettoken(void) {
    /* return the type of the next token and write token value to variable token */
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    /* return the last tokentype without updating it */
    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }

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