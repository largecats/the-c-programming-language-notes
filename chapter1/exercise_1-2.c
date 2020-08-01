/*
Exercise 1-2. Experiment to find out what happens when prints’s argument string contains \c, where c is some character not
listed above
*/

#include<stdio.h>
int main()
{
 printf("Hello world\c\n");
}

/*
chapter1/exercise_1-2.c: In function ‘int main()’:
chapter1/exercise_1-2.c:4:9: warning: unknown escape sequence: '\c'
  printf("Hello world\c\n");
*/
