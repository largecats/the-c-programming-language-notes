#include <stdio.h>
#include <ctype.h>
#include "header.h"

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, d, getch(void);
    void ungetch(int);
    char *w = word; /* pointer to pointer to char, i.e., pointer to string */

    while (isspace(c = getch())) {
        ; /* skip spaces */
    }
    /* check the first non-space characer */
    if (c != EOF) {
        /* if the first non-space character is not EOF, store in *w */
        *w++ = c;
    }
    if (!isalpha(c)) {
        /* if the first non-space character is not a letter */
        if (c == '\"') {
            /* skip string constant */
            c = getch();
            while (c != '\"') {
                c = getch();
            }
        }
        else if (c == '#') {
            /* skip preprocessor */
            c = getch();
            while (c != '\n') {
                c = getch();
            }
        }
        else if (c == '/') {
            /* skip comment */
            if ((c=getch()) == '/') { /*single comment*/
                for(c=getch(); c!= '\n'; c=getch()) 
                    ;
            }
            else if (c == '*') { /*mutiline comment*/
                for(c=getch(),d=getch(); c!= '*' && d!= '/'; c=getch(), d=getch()) 
                    ungetch(d);
            }
            else ungetch(c);
        }
        else {
            /* skip underscore and anything else */
            c = getch();
            while (!isspace(c) && c != EOF) {
                c = getch();
            }
        }
        if (c != '\"' && c != '\n' && c != '/') {
            ungetch(c);
        }
        *w = '\0';
        return c;
    }
    /* continue reading the renamining characters in the word until meeting a character that is not a letter, number, or _, which means that the word has ended */
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w); /* put it back */
            break; /* exit the for loop */
        }
    }
    *w = '\0';
    return word[0];
}