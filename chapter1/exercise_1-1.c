/*
Exercise 1-1. Run the ‘‘hello, world’’ program on your system. Experiment with leaving out parts of the program, to see
what error messages you get.
*/

#include<stdio.h>
int main()
{
 printf("Hello world\n");
}

/*
Comment out #include<stdio.h>
chapter1/exercise_1-1.c: In function ‘int main()’:
chapter1/exercise_1-1.c:4:2: error: ‘printf’ was not declared in this scope
  printf("Hello world\n");
  ^~~~~~
chapter1/exercise_1-1.c:4:2: note: suggested alternative: ‘int’
  printf("Hello world\n");
  ^~~~~~
  int

Comment out int main()
chapter1/exercise_1-1.c:3:1: error: expected unqualified-id before ‘{’ token
 {
 ^
The terminal process terminated with exit code: 1

Comment out {
chapter1/exercise_1-1.c:4:2: error: expected initializer before ‘printf’
  printf("Hello world\n");
  ^~~~~~
chapter1/exercise_1-1.c:5:1: error: expected declaration before ‘}’ token
 }
 ^
The terminal process terminated with exit code: 1

Comment out }
chapter1/exercise_1-1.c: In function ‘int main()’:
chapter1/exercise_1-1.c:4:25: error: expected ‘}’ at end of input
  printf("Hello world\n");
                         ^
The terminal process terminated with exit code: 1
*/