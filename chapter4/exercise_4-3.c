/*
Exercise 4-3. Given the basic framework, it’s straightforward to extend the calculator. Add the modulus (%) operator and
provisions for negative numbers.
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
main() {
    int type;
    double op2;
    char s[MAXOP];

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
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                op2 = pop();
                if(op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

/*******************************************/

#define MAXVAL 100

int sp = 0;
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

/*******************************************/
#include <ctype.h>
#include <string.h>

int getch(void);
void ungetch(int);

/* reads operator or operand from input one at a time and store in s*/
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0'; /* initialize s to contain c, the first character read */
    if (!isdigit(c) && c != '.' && c != '-') { /* check if c is an operator besides the minus operator - */
        return c;
    }
    else {
        i = 0;
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

/*******************************************/
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0; /* next free position in buf */

int getch(void) {
    return (bufp > 0)? buf[--bufp]: getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    }
    else {
        buf[bufp++] = c;
    }
}