#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

int getch(void);
void ungetch(int);

int getop(char s[]) {
    static int temp = '\0'; /* static variable is initialized only at the first time getop is called */
    int i, c;

    if (temp == '\0') {
        c = getch();
    }
    else {
        c = temp;
        temp = '\0';
    }
    while ((s[0] = c) == ' ' || c == '\t') {
        c = getch();
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c; /* not a number */
    }
    i = 0;
    if (isdigit(c)) { /* read integer part */
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    if (c == '.') { /* read fraction part, if any */
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
        temp = c; /* store in temp */
    }
    return NUMBER;
}