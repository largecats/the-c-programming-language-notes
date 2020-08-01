/*
Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the command line, where each
operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 * (3+4).
*/

/*
Actually cannot test using * coz it translates to names of all files in the directory.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h"
#include "../helper_functions.h"

int getop(char *arg);

/* expr: evaluates reverse Polish expression from command line */
int main(int argc, char *argv[]) {
    int i, op2;

    i = 0;
    while (++i < argc) {
        char *s;
        s = argv[i];
        // print_string(s);
        switch(getop(s)) {
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
            default:
                printf("error: unknown command");
                break;
        }
    }
    printf("\t %8g\n",pop());
    return 0;
}

int getop(char *arg) {
    int c;

    c = *arg;
    if (!isdigit(c)) {
        return c;
    }
    if (isdigit(c)) {
        return NUMBER;
    }
}

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
