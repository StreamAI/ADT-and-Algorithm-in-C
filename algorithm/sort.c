#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX_COUNT      50000
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

void insert_sort_TailRecursive(int *data, int n, int k, int step)
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

    insert_sort_TailRecursive(data, n, k + step, step);
}

void insert_sort(int *data, int n, int k, int step)
{
    while(k < n)
    {
        int i = k - step, temp = data[k];
        while (i >= 0 && data[i] > temp)
        {
            data[i + step] = data[i];
            i -= step;
        }
        data[i + step] = temp;

        k += step; 
    }
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

void bubble_sort(int *data, int n)
{
    int i, j;
    bool flag;

    for(i = 0; i < n; i++)
    {
        flag = true;
        for(j = 1; j < n - i; j++)
        {
            if(data[j] < data[j-1])
            {
                swap_data(&data[j], &data[j-1]);
                flag = false;
            }
        }
        if(flag == true)
            break;
    }
}

void select_sort(int *data, int n)
{
    int i,j, min;
	for(i = 0; i < n; i++)
    {
        min = i;
        for(j = i + 1; j < n; j++)
        {
            if(data[j] < data[min])
                min = j;
        }
        if(min != i)
            swap_data(&data[i], &data[min]);
    }
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

void count_sort(int *data, int n)
{
    // Find the maximum and minimum values
    int i, min = 0, max = 0;
    for (i = 0; i < n; i++)
    {
        if(data[i] > max)
            max = data[i];
        if(data[i] < min)
            min = data[i];
    }
    // Allocate space for count array
    int *temp = malloc((max - min + 1) * sizeof(int));
    if(temp == NULL)
        return;
    memset(temp, 0, ((max - min + 1) * sizeof(int)));
    // Count the number of times each element appears
    for(i = 0; i < n; i++)
        temp[data[i] - min]++;
    // Sum of count array accumulation
    for (i = 1; i < (max - min + 1); i++)
        temp[i] += temp[i - 1];
    // Allocate space for sorted elements of storage
    int *res = malloc(n * sizeof(int));
    if(res == NULL)
        return;
    // Put the element in the right place
    for(i = n - 1 ; i >= 0; i--)
    {
        int count = temp[data[i] - min];
        if(count > 0)
        {
        	res[count - 1 + min] = data[i];
        	temp[data[i] - min]--;
        }
    }
    // Copy an ordered array to the original
    for (i = 0; i < n; i++)
        data[i] = res[i];
    // Free temporarily allocated space
    free(res);
    free(temp);
}


struct HeapStruct{
    int capacity;
    int size;
    int *Array;
};
typedef struct HeapStruct *pHeap;

void heap_insert(pHeap H, int x)
{
    if(H->size >= H->capacity)
        return;

    int i;
    H->Array[H->size] = x;
    H->size++;
    // 自下往上堆化
    for(i = H->size - 1; i - 1 >= 0 && H->Array[i] > H->Array[(i-1)/2]; i = (i-1)/2)
        swap_data(&H->Array[i], &H->Array[(i-1)/2]);
}

pHeap build_heap(int *data, int n)
{
    pHeap H = malloc(sizeof(struct HeapStruct));
    if(H == NULL)
    {
        printf("Out of space.");
        return NULL;
    }

    int i;
    H->Array = data;
    H->capacity = n;
    H->size = 0;
    
    for(i = 0; i < n; i++)
        heap_insert(H, data[i]);

    return H;
}

int heap_removeTop(pHeap H)
{
    if(H->size <= 0)
        return -1;

    int i, maxPos;
    int top = H->Array[0];
    swap_data(&H->Array[0], &H->Array[H->size - 1]);
    H->size--;
    // 自上往下堆化
    for(i = 0; (2 * i + 1) <= H->size - 1; i = maxPos)
    {
        maxPos = i;
        if(H->Array[i] < H->Array[2 * i + 1])
            maxPos = 2 * i + 1;
        if((2 * i + 2) <= H->size - 1 && H->Array[maxPos] < H->Array[2 * i + 2])
            maxPos = 2 * i + 2;
        if(maxPos == i)
            break;

        swap_data(&H->Array[i], &H->Array[maxPos]);
    }

    return top;
}

void heap_sort(int *data, int n)
{
    pHeap H = build_heap(data, n);
    if(H == NULL)
        return;

    while(H->size > 0)
        heap_removeTop(H);

    free(H);
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
    printf("bubble sort: 6\n");
    printf("select sort: 7\n");
    printf("count  sort: 8\n");
    printf("heap   sort: 9\n");
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

    case 6:
        bubble_sort(data, MAX_COUNT);
        break;

    case 7:
        select_sort(data, MAX_COUNT);
        break;

    case 8:
        count_sort(data, MAX_COUNT);
        break;

    case 9:
        heap_sort(data, MAX_COUNT);
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