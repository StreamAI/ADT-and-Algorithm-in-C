#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COUNT      10000
#define SHOW_COUNT     100

int *data = NULL;

int * data_init(int *data, int n)
{
    int i;

    data = malloc(n * sizeof(int));

    srand(time(NULL));

    for(i = 0; i < n; i++)
        data[i] = rand() % n;

    return data;
}

void show_data(int *data, int n)
{
    int i;

    printf("data show:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d  ", data[i]);
    }
    printf("\n\n");
}

void insert_sort(int *data, int n, int k, int step)
{
    if(k >= n)
        return;
    
    int i = k - step, temp = data[k];
    while (i >= 0 && data[i] > temp)
    {
        data[i + step] = data[i];
        i -= step;
    }
    data[i + step] = temp; 

    insert_sort(data, n, k+ step, step);
}

void shell_sort(int *data, int n, int step)
{
    if(step < 1)
        return;

    int i;
    for(i = 0; i < step; i++)
        insert_sort(data, n, i, step);
    
    shell_sort(data, n, step / 2);
}

int main(void)
{
    int k, n;
    clock_t start, end;
    double time;

    printf("insert sort: 1\n");
    printf("shell  sort: 2\n");
    printf("Select method: ");
    scanf("%d", &k);

    data = data_init(data, MAX_COUNT);

    start = clock();
    switch (k)
    {
    case 1:
        insert_sort(data, MAX_COUNT, 1, 1);
        break;

    case 2:
        shell_sort(data, MAX_COUNT, MAX_COUNT / 2);
        break;
    
    default:
        break;
    }
    end = clock();
    time = (double)(end - start) / (CLOCKS_PER_SEC / 1000);

    show_data(data, SHOW_COUNT);
    printf("execution time: %.3lf ms.\n", time);

    free(data);
    return 0;
}