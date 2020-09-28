/*
Exercise 7-9. Functions like isupper can be implemented to save space or to save time. Explore both possibilities.

https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_7:Exercise_9
https://stackoverflow.com/questions/2169261/c-isupper-function
https://en.wikipedia.org/wiki/Space%E2%80%93time_tradeoff
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../../helper_functions.h"

#define N 10000

int isupper1(char c);
int isupper2(char c);
char random_letter(void);

int main() {
    clock_t start, end;
    double cpu_time_used1, cpu_time_used2;

    start = clock();
    for (int i = 0; i < N; i++) {
        char c = random_letter();
        print_variable(isupper1(c));
    }
    end = clock();
    cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC / N;

    start = clock();
    for (int i = 0; i < N; i++) {
        char c = random_letter();
        print_variable(isupper2(c));
    }
    end = clock();
    cpu_time_used2 = ((double) (end - start)) / CLOCKS_PER_SEC / N;

    printf("isuppser1: %f\n", cpu_time_used1);
    printf("isuppser2: %f\n", cpu_time_used2);
    return 0;
}

/*
$ gcc chapter7/7.8/exercise_7-9/main.c helper_functions.c -o chapter7/7.8/exercise_7-9/result.out

$ chapter7/7.8/exercise_7-9/result.out
...
isuppser1: 0.000109
isuppser2: 0.000016
*/

/* random_letter: returns random letter in a-zA-z */
char random_letter(void) {
    int c = rand();
    if (rand() % 2) {
        return 'A' + c % 26;
    }
    else {
        return 'a' + c % 26;
    }
    
}

/* isupper1: save space */
int isupper1(char c) {
    return (c >= 'A') && (c <= 'Z');
}

/* isupper2: save time? */
int isupper2(char c) {
    return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
}