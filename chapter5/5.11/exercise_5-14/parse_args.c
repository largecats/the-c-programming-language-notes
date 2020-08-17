#include <stdio.h>
#include "../../../helper_functions.h"
#include "extern.h"

void parse_args(int argc, char *argv[], int *n, int *r) {
    int i = 0;

    while (++i < argc) {
        if (strcmp(argv[i], "-n") == 0) {
            *n = 1;
        }
        if (strcmp(argv[i], "-r") == 0) {
            *r = 1;
        }
    }
}