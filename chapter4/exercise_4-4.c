/*
Exercise 4-4. Add the commands to print the top elements of the stack without popping, to duplicate it, and to swap the top
two elements. Add a command to clear the stack.
*/

/*
Note that case '\n' will always pop() whenever ENTER is pressed, including when invoking the commands top, duplicate, swap, and clear.
So printing the top element of the stack will always be accompanied by a pop() from case '\n'.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void top(void);
void duplicate(void);
void swap(void);
void clear(void);

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
            case 't': /* print top element */
                top();
                break;
            case 'd': /* duplicate top element */
                duplicate();
                break;
            case 's': /* swap the first two elements */
                swap();
                break;
            case 'c': /* clear stack */
                clear();
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

void top(void) {
    if (sp > 0) {
        printf("%g\n", val[sp-1]);
    }
    else {
        printf("error: stack empty\n");
    }
    // printf("sp = %d\n", sp);
}

void duplicate(void) {
    if (sp > 0) {
        double e = pop();
        push(e);
        push(e);
    }
    else {
        printf("error: stack empty\n");
    }
    // printf("sp = %d\n", sp);
}

void swap(void) {
    if (sp > 0) {
        if (sp > 1) {
            double e1 = pop();
            double e2 = pop();
            push(e1);
            push(e2);
        }
        else {
            printf("error: not enough elements to swap\n");
        }
    }
    else {
        printf("error: stack empty\n");
    }
    // printf("sp = %d\n", sp);
}

void clear(void) {
    sp = 0;
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