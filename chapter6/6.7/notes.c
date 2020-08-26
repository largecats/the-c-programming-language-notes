#include <stdio.h>
#include "../../helper_functions.h"

int main() {
    typedef char *String;
    String s = "hello";
    print_string(s);

    union u_tag {
        int ival;
        float fval;
        char *sval;
    } u;
    u.ival = 1;
    print_variable(u.ival);
    print_variable(&(u.ival));
    u.sval = "hello";
    print_string(u.sval);
    print_variable(&(u.sval)); // same address

    struct {
        unsigned int is_keyword: 1;
        unsigned int is_extern: 1;
        unsigned int is_static: 1;
    } flags;

    flags.is_extern = 1;
    flags.is_static = 1;
    if (flags.is_extern && flags.is_static) {
        // https://stackoverflow.com/questions/2841762/why-wont-extern-link-to-a-static-variable
        printf("error: extern and static cannot appear simultaneously\n");
    }
}

/*
$ gcc chapter6/6.7/notes.c helper_functions.c -o chapter6/6.7/result.out

$ chapter6/6.7/result.out
s = hello
u.ival = 1
&(u.ival) = -772380120
u.sval = hello
&(u.sval) = -772380120
error: extern and static cannot appear simultaneously
*/