/*
Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution
speed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../helper_functions.h"
#include "header.h"

#define N 10000

FILE1 _iob1[OPEN_MAX];
FILE2 _iob2[OPEN_MAX];

int main(){
    clock_t start, end;
    double cpu_time_used1, cpu_time_used2;

    start = clock();
    for (int i=0; i<N; i++) {
        FILE1 *fp1 = fopen1("chapter8/8.5/exercise_8-2/hello1.txt","r");
        if (fp1 != NULL) {	
            char c1;
            while ((c1=getc1(fp1)) != EOF) {
                putchar(c1);
            }
        }
        else {
            printf("Failed to open file");
        }
        fclose1(fp1);
    }
    end = clock();
    cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC / N;
    
    start = clock();
    for (int i=0; i<N; i++) {
        FILE2 *fp2 = fopen2("chapter8/8.5/exercise_8-2/hello2.txt","r");
        if (fp2 != NULL) {	
            char c2;
            while ((c2=getc2(fp2)) != EOF) {
                putchar(c2);
            }
        }
        else {
            printf("Failed to open file");
        }
        fclose2(fp2);
    }
    end = clock();
    cpu_time_used2 = ((double) (end - start)) / CLOCKS_PER_SEC / N;
	
    printf("1: %f\n", cpu_time_used1);
    printf("2: %f\n", cpu_time_used2);
	return 0;
}

/*
$ gcc chapter8/8.5/exercise_8-2/main.c chapter8/8.5/exercise_8-2/fillbuf.c chapter8/8.5/exercise_8-2/fopen.c helper_functions.c -o chapter8/8.5/exercise_8-2/result.out

$ chapter8/8.5/exercise_8-2/result.out
hello1
...
hello2
...
1: 0.000248
2: 0.000223
*/

int fclose1(FILE1 *fp) {
    if (fp == NULL) {
        return -1;
    }
    fp->cnt = 0;
    fp->ptr = NULL;
    if (fp->base != NULL) {
        /* if a buffer was allocated, free its storage */
        free(fp->base);
        fp->base = NULL;
    }
    fp->flag = 0;
    int fdTemp = fp->fd;
    fp->fd = -1; /* file descriptor is positive */
    return close(fdTemp);
}

int fclose2(FILE2 *fp) {
    if (fp == NULL) {
        return -1;
    }
    fp->cnt = 0;
    fp->ptr = NULL;
    if (fp->base != NULL) {
        /* if a buffer was allocated, free its storage */
        free(fp->base);
        fp->base = NULL;
    }
    fp->flag._READ = 0;
    fp->flag._WRITE = 0;
    fp->flag._UNBUF = 0;
    fp->flag._EOF = 0;
    fp->flag._ERR = 0;
    int fdTemp = fp->fd;
    fp->fd = -1; /* file descriptor is positive */
    return close(fdTemp);
}