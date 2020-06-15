#include <stdio.h>
#include <ctype.h>
#include "calc.h"

// int getop(char s[]) {
//     int i, c;

//     while ((s[0] = c = getch()) == ' ' || c == '\t') {
//         ;
//     }
//     s[1] = '\0';
//     if (!isdigit(c) && c != '.') {
//         return c; /* not a number */
//     }
//     i = 0;
//     if (isdigit(c)) { /* read integer part */
//         while (isdigit(s[++i] = c = getch())) {
//             ;
//         }
//     }
//     if (c == '.') { /* read fraction part, if any */
//         while (isdigit(s[++i] = c = getch())) {
//             ;
//         }
//     }
//     s[i] = '\0';
//     if (c != EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
//         ungetch(c);
//     }
//     return NUMBER;
// }

int getop(char *s) {
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t') {
        ;
    }
    *++s = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    if (isdigit(c)) {
        while (isdigit(*++s = c = getch())) {
            ;
        }
    }
    if (c == '.') {
        while (isdigit(*++s = c = getch())) {
            ;
        }
    }
    *s = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}