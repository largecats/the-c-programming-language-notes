#include <stdio.h>
#include <string.h>
#include "../helper_functions.h"

int main(int argc, char *argv[]) { // won't raise error because array parameter is passed as pointer
// int main() {
    // char *argv[] = {"echo", "hello", "world"}; // will raise error since cannot modify array address
    print_char((*++argv)[0]);
    print_char(*++(argv[0]));
}

/*
$ gcc scratch.c -o result.out
$ ./result.out
(*++argv)[0] = h
*++(argv[0]) = e
*/