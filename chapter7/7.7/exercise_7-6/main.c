/*
Exercise 7-6. Write a program to compare two files, printing the first line where they differ.
*/

#include <stdio.h>
#include <string.h>
#include "../../../helper_functions.h"

#define MAXLINE 100

int main(int argc, char *argv[]) {
    char s1[MAXLINE], s2[MAXLINE];
    char *r1, *r2;
    int lineNo = 0;

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

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
*/