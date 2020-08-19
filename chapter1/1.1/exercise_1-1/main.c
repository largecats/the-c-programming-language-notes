/*
Exercise 1-1. Run the ‘‘hello, world’’ program on your system. Experiment with leaving out parts of the program, to see
what error messages you get.
*/

#include <stdio.h>

int main() 
{
  printf("Hello world\n");
}

/*
Comment out #include <stdio.h>

$ gcc chapter1/1.1/exercise_1-1/main.c -o chapter1/1.1/exercise_1-1/result.out
chapter1/1.1/exercise_1-1/main.c: In function ‘main’:
chapter1/1.1/exercise_1-1/main.c:9:3: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
    9 |   printf("Hello world\n");
      |   ^~~~~~
chapter1/1.1/exercise_1-1/main.c:9:3: warning: incompatible implicit declaration of built-in function ‘printf’
chapter1/1.1/exercise_1-1/main.c:1:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
  +++ |+#include <stdio.h>
    1 | /*

$ chapter1/1.1/exercise_1-1/result.out
Hello world
*/

/*
Comment out int main()

$ gcc chapter1/1.1/exercise_1-1/main.c -o chapter1/1.1/exercise_1-1/result.out
chapter1/1.1/exercise_1-1/main.c:9:1: error: expected identifier or ‘(’ before ‘{’ token
    9 | {
      | ^
*/

/*
Comment out {

$ gcc chapter1/1.1/exercise_1-1/main.c -o chapter1/1.1/exercise_1-1/result.out
chapter1/1.1/exercise_1-1/main.c: In function ‘main’:
chapter1/1.1/exercise_1-1/main.c:10:3: error: expected declaration specifiers before ‘printf’
   10 |   printf("Hello world\n");
      |   ^~~~~~
chapter1/1.1/exercise_1-1/main.c:11:1: error: expected declaration specifiers before ‘}’ token
   11 | }
      | ^
chapter1/1.1/exercise_1-1/main.c:57: error: expected ‘{’ at end of input
   57 | * /
      |
*/

/*
Comment out }

$ gcc chapter1/1.1/exercise_1-1/main.c -o chapter1/1.1/exercise_1-1/result.out
chapter1/1.1/exercise_1-1/main.c: In function ‘main’:
chapter1/1.1/exercise_1-1/main.c:10:3: error: expected declaration or statement at end of input
   10 |   printf("Hello world\n");
      |   ^~~
*/