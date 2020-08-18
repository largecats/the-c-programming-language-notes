#include <stdio.h>
#include <stdlib.h>
#include "../../../helper_functions.h"
#include "extern.h"

void parse_arg(int argc, char *argv[], int *mp, int *np) {
    int i = 1;

    while (i < argc) {
        switch (*argv[i]) {
            case '-':
                *mp = atoi(++(argv[i]));
            case '+':
                *np = atoi(++(argv[i]));
                break;
            default:
                break;
        }
        i++;
    }
}