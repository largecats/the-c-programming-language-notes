#include <stdio.h>
#include <string.h>
#include <math.h>
#include "calc.h"

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

void func(char s[]) {
    if (strcmp(s, "sin") == 0) {
        push(sin(pop())); /* returns angle in radians */
    }
    else if (strcmp(s, "exp") == 0) {
        push(exp(pop()));
    }
    else if (strcmp(s, "pow") == 0) {
        double temp = pop();
        push(pow(pop(), temp));
    }
    else {
        printf("error: function not supported\n");
    }
}