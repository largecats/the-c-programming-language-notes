#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../helper_functions.h"
#include "header.h"

void parse_args(int argc, char *argv[], int *np) {
    int i = 0;

    while (++i < argc) {
        // print_string(argv[i]);
        if (strcmp(argv[i], "-n") == 0) {
            *np = atoi(argv[i+1]);
        }
    }
}