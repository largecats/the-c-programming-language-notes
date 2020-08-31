/*
Exercise 7-6. Write a program to compare two files, printing the first line where they differ.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../helper_functions.h"

#define MAXLINE 100

int main(int argc, char *argv[]) {
    char s1[MAXLINE], s2[MAXLINE], *r1, *r2, *prog;
    int lineNo = 0;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments: %d\n", argc);
        exit(1);
    }

    prog = argv[0];

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", prog, argv[2]);
        exit(1);
    }

    while ((r1 = fgets(s1, MAXLINE, fp1)) != NULL && (r2 = fgets(s2, MAXLINE, fp2)) != NULL) {
        lineNo++;
        if (strcmp(r1, r2) != 0) {
            printf("Found difference at line %d:\n", lineNo);
            print_string(r1);
            print_string(r2);
            break;
        }
    }
    if ((r1 == NULL && r2 != NULL) || (r1 != NULL && r2 == NULL)) {
        printf("Found difference at line %d:\n", lineNo);
        print_string(r1);
        print_string(r2);
    }
    else {
        return 0;
    }
}

/*
$ gcc chapter7/7.7/exercise_7-6/main.c -o chapter7/7.7/exercise_7-6/result.out

$ chapter7/7.7/exercise_7-6/result.out chapter7/7.7/exercise_7-6/h1.txt chapter7/7.7/exercise_7-6/h2.txt
Found difference at line 2:
r1 = do you read me
r2 = (null)

$ chapter7/7.7/exercise_7-6/result.out chapter7/7.7/exercise_7-6/h1.txt
Invalid number of arguments: 2

$ chapter7/7.7/exercise_7-6/result.out chapter7/7.7/exercise_7-6/h1.txt chapter7/7.7/exercise_7-6/h3.txt
chapter7/7.7/exercise_7-6/result.out: can't open chapter7/7.7/exercise_7-6/h3.txt
*/