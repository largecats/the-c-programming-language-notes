#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

int getch(void);
void ungetch(int);

/* reads operator or operand from input one at a time and store in s*/
int getop(char s[]) {
    int i, c;
    int getop(char s[]);

    while ((s[0] = c = getch()) == ' ' || c =='\t') {
        ;
    }
    s[1] = '\0'; /* initialize s to contain c, the first character read */
    if (!isdigit(c) && c!='.') {
        return c;
    }
    
    i = 0;
    if (isdigit(c)) {
        while(isdigit(s[++i] =c =getch())) {
            ;
        }
    }

    if (c=='.') { /* continue reading fractional part of the operand, if any */
        while (isdigit(s[++i] = c=getch())) {
            ;
        }
    }
    
    s[i] = '\0';
    if (c!=EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
        ungetch(c);
    }
    return NUMBER;
}