#include <stdio.h>
#include "../../helper_functions.h"

int main() {
    char s[] = "hello";
    char *cs;

    cs = s;
    cs++;
    print_string(cs);
    print_string(s);
}

/*
$ gcc chapter7/7.7/scratch.c -o chapter7/7.7/result.out

$ chapter7/7.7/result.out
cs = ello
s = hello
*/