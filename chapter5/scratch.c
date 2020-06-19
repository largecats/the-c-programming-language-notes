#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../helper_functions.h"

int main() {
    print_variable('A');
    print_variable('a');
    print_variable('Z');
    printf("%f\n", atof("A"));
    printf("%f\n", atof("a"));

    return 0;
}