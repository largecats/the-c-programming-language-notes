
#include <stdio.h>
#include <string.h>
#include "calc.h"

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void print_val(void) {
    printf("stack = ");
    while (sp >= 0) { /* use stack pointer instead of array index since the data structure is stack, not array*/
        printf("%f", val[sp--]);
    }
    putchar('\n');
}

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