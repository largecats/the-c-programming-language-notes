/*
Exercise 7-1. Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked
with, as found in argv[0].
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char c;

    if (strcmp(argv[0], "chapter7/7.1/exercise_7-1/lower") == 0) {
        while ((c=getchar()) != EOF) {
            putchar(tolower(c));
        }
    }
    else if (strcmp(argv[0], "chapter7/7.1/exercise_7-1/upper") == 0) {
        while ((c=getchar()) != EOF) {
            putchar(toupper(c));
        }
    }
    else {
        while ((c=getchar()) != EOF) {
            putchar(c);
        }
    }
    return 0;
}

/*
$ gcc chapter7/7.1/exercise_7-1/main.c -o chapter7/7.1/exercise_7-1/lower
$ chapter7/7.1/exercise_7-1/lower
Hello Neo
hello neo
Knock Knock
knock knock
The Matrix has you
the matrix has you

$ gcc chapter7/7.1/exercise_7-1/main.c -o chapter7/7.1/exercise_7-1/upper
$ chapter7/7.1/exercise_7-1/upper
hello neo
HELLO NEO
knock knock
KNOCK KNOCK
*/