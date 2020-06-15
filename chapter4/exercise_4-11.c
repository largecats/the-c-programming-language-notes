/*
Exercise 4-11. Modify getop so that it doesn’t need to use ungetch. Hint: use an internal static variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP]; /* store op read from input */

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                }
                else {
                    printf("error: zero division");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command");
                break;
        }
    }
    return 0;
}

/*****************************************/
#include <stdio.h>
#include "calc.h"

#define MAXVAL 100
int sp = 0; /* next free stack position */
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    }
    else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void) {
    if (sp > 0) {
        return val[--sp]; /* last occupied stack position */
    }
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


/************************************/
#include <ctype.h>
#include <string.h>

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

/*******************************/
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0; /* next free position in buf */

int getch(void) { /* get character from buffer */
    return (bufp > 0)? buf[--bufp]: getchar(); /* get from last occupied position in buf */
}

// void ungetch(int c) { /* push character back to buffer */
//     if (bufp >= BUFSIZE) {
//         printf("ungetch: too many characters\n");
//     }
//     else {
//         buf[bufp++] = c;
//     }
// }
