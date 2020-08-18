#include <stdio.h>
#include <string.h>
#include "../../helper_functions.h"

int main(int argc, char *argv[]) { // won't raise error because array parameter is passed as pointer
// int main() {
    // char *argv[] = {"echo", "hello", "world"}; // will raise error since cannot modify array address
    print_char((*++argv)[0]);
    print_char(*++(argv[0]));
}

/*
$ gcc chapter5/5.10/argv_notes.c -o chapter5/5.10/result.out
$ chapter5/5.10/result.out hello
(*++argv)[0] = h
*++(argv[0]) = e
*/

/*
If no argument is supplied, will raise segmentation fault.
$ chapter5/5.10/result.out
Segmentation fault (core dumped)
*/