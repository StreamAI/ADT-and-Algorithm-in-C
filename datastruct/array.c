#include <stdio.h>

int main(void)
{
    // Create a one-dimensional array
    int a[6] = {1, 3, 4, 5};
    printf("a    = %X, *a   = %d\n", a, *a);
    printf("a[0] = %d, a[1] = %d\n", a[0], a[1]);

    // Modifying array element values
    a[1] = 7;

    // Accessing array element values
    for(int i = 0; i < 6; i++)
        printf("a[%d] = %d\n", i, a[i]);
    printf("\n");

    // Create a two-dimensional array
    int b[][3] = {{1, 2}, {3, 4, 5}, {7}};
    printf("b    = %X, *b = %X, **b     = %d\n", b, *b, **b);
    printf("b[0] = %X, b[0][0] = %d, b[1][1] = %d\n", b[0], b[0][0], b[1][1]);
    
    // Modifying array element values
    b[1][1] = 11;
    
    // Accessing array element values
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("b[%d][%d] = %d\t", i, j, b[i][j]);
        printf("\n");
    }
    printf("\n");

    return 0;
}