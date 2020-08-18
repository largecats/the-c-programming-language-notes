#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

int getch(void);
void ungetch(int);

/* reads operator or operand from input one at a time and store in s*/
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0'; /* initialize s to contain c, the first character read */
    i = 0;
    if (islower(c)) { /* check if c is lowercase letter, i.e., the start of a function */
        while (islower(s[++i] = c = getch())) {
            ;
        }
        s[i] = '\0';
        if (c != EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
            ungetch(c);
        }
        return FUNC;
    }
    else {
        if (!isdigit(c) && c != '.' && c != '-') { /* check if c is an operator besides the minus operator - */
            return c;
        }
        else {
            if (isdigit(c) || c == '-') { /* read operand along with possible negative sign - */
                while (isdigit(s[++i] = c = getch())) {
                    ;
                }
            }
            if (c == '.') { /* continue reading fractional part of the operand, if any */
                while (isdigit(s[++i] = c = getch())) {
                    ;
                }
            }
            s[i] = '\0';
            if (c != EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
                ungetch(c);
            }
            if (strcmp(s, "-") == 0) { /* if s is the minus operator, return the minus operator */
                return '-';
            }
            else { /* if s is not the minus operator, it must be a number */
                return NUMBER;
            }
        }
    }
}
