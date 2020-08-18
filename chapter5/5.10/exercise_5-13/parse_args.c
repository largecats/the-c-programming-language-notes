#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

void parse_args(int argc, char *argv[], int *np) {
    int i = 0;

    while (++i < argc) {
        switch (*argv[i]) {
            case '-': 
                *np = atoi(++(argv[i]));
                break;
            default:
                break;
        }
    }
}