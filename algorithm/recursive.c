#include <stdio.h>

int factorial_iterative(int n)
{
    if(n < 0)
        return 0;
    
    int i, res = 1;
    
    for(i = 1; i <= n; i++)
        res *= i;
    
    return res;
}

int factorial_recursive(int n)
{
    if(n < 0)
        return 0;
    else if(n == 0)
        return 1;
    else
        return n*factorial_recursive(n-1);
}

int factorial_Tailrecursive(int n, int res)
{
    if(n < 0)
        return 0;
    else if(n == 0)
        return res;
    else
        return factorial_Tailrecursive(n-1, n*res);
}

int fibonacci_iterative(int n)
{
    if(n < 0)
        return 0;

    int i, temp, res1 = 1, res2 = 1;
    for(i = 2; i <= n; i++)
    {
        temp = res1;
        res1 = res2;
        res2 += temp;
    }

    return res2;
}

int fibonacci_recursive(int n)
{
    if(n < 0)
        return 0;
    else if(n == 0 || n == 1)
        return 1;
    else
        return (fibonacci_recursive(n-1) + fibonacci_recursive(n-2));
}

#define MAXN    1000

int fibonacci[MAXN] = {0};

int fibonacci_recursive_memory(int n)
{
    if(n < 0)
        return 0;
    else if(n == 0 || n == 1)
        return 1;
    else if(fibonacci[n] != 0)
        return fibonacci[n];
    else
    {
        fibonacci[n] = fibonacci_recursive_memory(n-1) + fibonacci_recursive_memory(n-2);
        return fibonacci[n];
    }
}

int fibonacci_Tailrecursive(int n, int res1, int res2)
{
    if(n < 0)
        return 0;
    else if(n == 0)
        return res1;
    else if(n == 1)
        return res2;
    else
        return fibonacci_Tailrecursive(n-1, res2, res2 + res1);
}

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main(void)
{
    int k, n, m, res;

    printf("factorial_iterative function: 1\n");
    printf("factorial_recursive function: 2\n");
    printf("factorial_Tailrecursive function: 3\n");
    printf("fibonacci_iterative function: 4\n");
    printf("fibonacci_recursive function: 5\n");
    printf("fibonacci_recursive_memory function: 6\n");
    printf("fibonacci_Tailrecursive function: 7\n");
    printf("greatest common divisor function: 8\n");
    printf("select the number of function: ");
    scanf("%d", &k);

    switch (k)
    {
    case 1:
        printf("input one interge: ");
        scanf("%d", &n);
        res = factorial_iterative(n);
        printf("%d! = %d\n", n, res);
        break;

    case 2:
        printf("input one interge: ");
        scanf("%d", &n);
        res = factorial_recursive(n);
        printf("%d! = %d\n", n, res);
        break;

    case 3:
        printf("input one interge: ");
        scanf("%d", &n);
        res = factorial_Tailrecursive(n, 1);
        printf("%d! = %d\n", n, res);
        break;

    case 4:
        printf("input one interge: ");
        scanf("%d", &n);
        res = fibonacci_iterative(n);
        printf("fibonacci(%d) = %d\n", n, res);
        break;

    case 5:
        printf("input one interge: ");
        scanf("%d", &n);
        res = fibonacci_recursive(n);
        printf("fibonacci(%d) = %d\n", n, res);
        break;

    case 6:
        printf("input one interge: ");
        scanf("%d", &n);
        res = fibonacci_recursive_memory(n);
        printf("fibonacci(%d) = %d\n", n, res);
        break;

    case 7:
        printf("input one interge: ");
        scanf("%d", &n);
        res = fibonacci_Tailrecursive(n, 1, 1);
        printf("fibonacci(%d) = %d\n", n, res);
        break;

    case 8:
        printf("input two interge: ");
        scanf("%d %d", &n, &m);
        res = gcd(n, m);
        printf("gcd(%d, %d) = %d\n", n, m, res);
        printf("lcm(%d, %d) = %d\n", n, m, n*m/res);
        break;
    
    default:
        break;
    }
    printf("\n");
    return 0;
}