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
xiaolinfan@DESKTOP-FNKD3TG:/mnt/c/Users/xiaolinfan/Fun/programming/languages/languages/the-c-programming-language/chapter5$ gcc scratch.c -o result.out
xiaolinfan@DESKTOP-FNKD3TG:/mnt/c/Users/xiaolinfan/Fun/programming/languages/languages/the-c-programming-language/chapter5$ ./result.out hello world
(*++argv)[0] = h
*++(argv[0]) = e
*/