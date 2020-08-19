#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"
#include "../../../helper_functions.h"

#define MAXLINE 100
char line[MAXLINE];
int lp = 0; /* next position to read in the line */

int getline1(char s[], int lim);

/* reads operator or operand from input one at a time and store in s*/
int getop(char s[]) {
    int i, c;
    if (line[lp] == '\0') { /* if we have finished reading the line, read the next line */
        if (getline1(line, MAXLINE) == 0) {
            return EOF; /* getop now needs to return EOF explicitly as this is previously done by getch */
        }
        else {
            lp = 0; /* reset line pointer to first character in line */
        }
    }

    while ((s[0] = c = line[lp++]) == ' ' || c == '\t') { /* start reading from where we left off last time */
        ;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') { /* not a number */
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = line[lp++])) {
            ;
        }
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = line[lp++])) {
            ;
        }
    }
    s[i] = '\0';
    /* actually the following block will always be executed since c cannot be EOF now */
    if (c != EOF) { /* by now, if we haven't reached EOF, we would have read 1 position ahead to terminate the while loops */
        lp--;
    }
    return NUMBER;
}

void print_line(void) {
    int i = 0;
    printf("line = ");
    while (line[i] != '\0') {
        printf("%c", line[i++]);
    }
    putchar('\n');
}