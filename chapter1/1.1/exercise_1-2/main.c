/*
Exercise 1-2. Experiment to find out what happens when prints’s argument string contains \c, where c is some character not
listed above
*/

#include <stdio.h>

int main() {
  printf("Hello world\c\n");
}

/*
$ gcc chapter1/1.1/exercise_1-2/main.c -o chapter1/1.1/exercise_1-2/result.out
chapter1/1.1/exercise_1-2/main.c: In function ‘main’:
chapter1/1.1/exercise_1-2/main.c:9:10: warning: unknown escape sequence: '\c'
    9 |   printf("Hello world\c\n");

$ chapter1/1.1/exercise_1-2/result.out
Hello worldc
*/
