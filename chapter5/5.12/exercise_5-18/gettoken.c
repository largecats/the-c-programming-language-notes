#include <ctype.h>
#include <string.h>
#include "extern.h"
#include "../../../helper_functions.h"

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

int prevtoken = NO;

int gettoken(void) {
    /* return the type of the next token, write token value to variable token, and write token type to variable tokentype */
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
    
    /* handle error by returning the last tokentype and move on */
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