/*
Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution
speed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../helper_functions.h"
#include "header.h"

FILE1 _iob1[OPEN_MAX];
FILE2 _iob2[OPEN_MAX];

int main(){
    // for (int i=0; i<N; i++) {
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
    // fclose1(fp1);
    // }
    
    // for (int i=0; i<N; i++) {
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
    // fclose2(fp2);
    // }
	
	return 0;
}

/*
$ gcc chapter8/8.5/exercise_8-2/main.c chapter8/8.5/exercise_8-2/fillbuf.c chapter8/8.5/exercise_8-2/fopen.c helper_functions.c -o chapter8/8.5/exercise_8-2/result.out

$ chapter8/8.5/exercise_8-2/result.out
hello1
hello2
*/

// void fclose1(FILE1 *fp) {
//     close(fp->fd);
//     fp = NULL;
// }



// void fclose2(FILE2 *fp) {
//     close(fp->fd);
//     fp = NULL;
// }