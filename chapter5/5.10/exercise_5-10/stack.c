#include <stdio.h>
#include "calc.h"
#include "../../../helper_functions.h"

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
