/*
Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1.
*/

#include <stdio.h>

int main()
{
    int c = (getchar() != EOF);
    printf("%d\n", c);
}

/*
$ gcc chapter1/1.5.1/exercise_1-6/main.c -o chapter1/1.5.1/exercise_1-6/result.out

$ chapter1/1.5.1/exercise_1-6/result.out
hello
1
*/