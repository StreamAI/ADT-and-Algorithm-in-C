#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_COUNT      1000000
#define SHOW_COUNT     50

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

void show_data(int *data, int n, int m)
{
    int i;

    printf("data show:\n");
    for(i = 0; i < m; i++)
    {
        printf("%d  ", data[i]);
    }

    printf("\n......\n");   
    for(i = n - m; i < n; i++)
    {
        printf("%d  ", data[i]);
    }

    printf("\n\n");
}

bool validate_data(int *data, int n)
{
    bool res = true;
    int i;
    for (i = 1; i < n; i++)
    {
        if(data[i] < data[i - 1])
            res = false;
    }

    if(res == true)
        printf("\nThe data sequence has been ordered.\n\n");
    else
        printf("\nThe data sequence is unordered.\n\n");

    return res;
}

void swap_data(int *a, int *b)
{
    if(*a != *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
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

    insert_sort(data, n, k + step, step);
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

void merge_data(int *data, int *temp, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = 0;

    while(i <= mid && j <= right)
    {
        if(data[i] <= data[j])
            temp[k++] = data[i++];
        else
            temp[k++] = data[j++];
    }

    while(i <= mid)
        temp[k++] = data[i++];

    while(j <= right)
        temp[k++] = data[j++];

    for(i = left, k = 0; i <= right; i++, k++)
        data[i] = temp[k];
}

void recursive_merge(int *data, int *temp, int left, int right)
{
    if(left >= right)
        return;

    int mid = left + (right - left) / 2;
    recursive_merge(data, temp, left, mid);
    recursive_merge(data, temp, mid + 1, right);

    merge_data(data, temp, left, mid, right);
}

void merge_sort(int *data, int n)
{
    int *temp = malloc(n * sizeof(int));

    recursive_merge(data, temp, 0, n - 1);

    free(temp);
}

int partition(int *data, int left, int right)
{
    /*
    // 随机选择分界线或枢纽值
    int index = left + rand() % (right - left + 1);
    swap_data(&data[index], &data[right]);
    int i = left, j = right - 1, pivot = right;
    */
    // 三数取中法选择分界线或枢纽值
    int mid = left + (right - left) / 2;
    if(data[left] > data[mid])
        swap_data(&data[left], &data[mid]);
    if(data[left] > data[right])
        swap_data(&data[left], &data[right]);
    if(data[mid] > data[right])
        swap_data(&data[mid], &data[right]);

    swap_data(&data[mid], &data[right-1]);
    int i = left + 1, j = right - 2, pivot = right - 1;
    
    while (true)
    {
        while (data[i] < data[pivot])
            i++;

        while (j > left && data[j] >= data[pivot])
            j--;
        
        if(i < j)
            swap_data(&data[i], &data[j]);
        else
            break;
    }
    
    if(i < right)
        swap_data(&data[i], &data[pivot]);

    return i;
}

void quick_sort(int *data, int left, int right)
{
    if(right - left <= 1)
    {
        if(right - left == 1 && data[left] > data[right])
            swap_data(&data[left], &data[right]);
  
        return;
    }

    int divide = partition(data, left, right);
    quick_sort(data, left, divide - 1);
    quick_sort(data, divide + 1, right);
}

void quicksort(int *data, int n)
{
    if(n < 15)
        insert_sort(data, n, 1, 1);
    else
        quick_sort(data, 0, n - 1);
}

int compfunc(const void *a, const void *b)
{
    const int arg1 = *(const int *)a;
    const int arg2 = *(const int *)b;
    
    if(arg1 < arg2)
        return -1;
    if(arg1 > arg2)
        return 1;      
    return 0;
}

int main(void)
{
    int k, n;
    clock_t start, end;
    double time;

    printf("insert sort: 1\n");
    printf("shell  sort: 2\n");
    printf("merge  sort: 3\n");
    printf("quick  sort: 4\n");
    printf("qsort      : 5\n");
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

    case 3:
        merge_sort(data, MAX_COUNT);
        break;

    case 4:
        quicksort(data, MAX_COUNT);
        break;

    case 5:
        qsort(data, MAX_COUNT, sizeof(int), compfunc);
        break;
    
    default:
        break;
    }
    end = clock();
    time = (double)(end - start) / (CLOCKS_PER_SEC / 1000);

    //show_data(data, MAX_COUNT, SHOW_COUNT);
    validate_data(data, MAX_COUNT);
    printf("execution time: %.3lf ms.\n\n", time);

    free(data);
    return 0;
}