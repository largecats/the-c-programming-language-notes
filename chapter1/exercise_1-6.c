/*
Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1.
*/

#include <stdio.h>

main()
{
    int c = (getchar() != EOF);
    printf("%d", c);
}

/*
1
*/