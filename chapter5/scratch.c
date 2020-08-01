#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../helper_functions.h"

int main() {
    char *token, *string, *tofree;

    tofree = string = strdup("abc,def,ghi");

    while ((token = strsep(&string, ",")) != NULL)
        printf("%s\n", token);

    free(tofree);

    return 0;
}