#include <stdio.h>
#include <ctype.h>
#include "calc.h"
#include "../../../helper_functions.h"

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