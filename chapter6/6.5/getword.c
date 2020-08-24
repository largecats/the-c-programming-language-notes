#include <stdio.h>
#include <ctype.h>

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
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
        /* if the first non-space character is not a letter, terminate and return it */
        *w = '\0';
        return c;
    }
    /* continue reading the renamining characters in the word until meeting a character that is not a letter or number, which means that the word has ended */
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w); /* put it back */
            break; /* exit the for loop */
        }
    }
    *w = '\0';
    return word[0];
}