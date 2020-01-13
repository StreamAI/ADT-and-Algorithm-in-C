#include <stdio.h>
#include <stdlib.h>

#define DataType    int

struct HeapStruct{
    int capacity;
    int size;
    DataType *Array;
};
typedef struct HeapStruct *pHeap;

void swap_data(int *a, int *b)
{
    if(*a != *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

pHeap Heap_Create(int capacity)
{
    pHeap H = malloc(sizeof(struct HeapStruct));
    if(H == NULL)
    {
        printf("Out of space.");
        return NULL;
    }

    H->Array = malloc((capacity + 1) * sizeof(DataType));
    if(H->Array == NULL)
    {
        printf("Out of space.");
        free(H);
        return NULL;
    }

    H->capacity = capacity;
    H->size = 0;
    return H;
}

void Heap_Insert(pHeap H, DataType x)
{
    if(H->size >= H->capacity)
        return;

    int i;
    H->size++;
    H->Array[H->size] = x;
    // 自下往上堆化
    for(i = H->size; i/2 > 0 && H->Array[i] > H->Array[i/2]; i /= 2)
        swap_data(&H->Array[i], &H->Array[i/2]); 
}

DataType Heap_RemoveTop(pHeap H)
{
    if(H->size <= 0)
        return -1;

    int i, maxPos;
    H->Array[0] = H->Array[1];
    H->Array[1] = H->Array[H->size];
    H->size--;
    // 自上往下堆化
    for(i = 1; 2 * i <= H->size; i = maxPos)
    {
        maxPos = i;
        if(H->Array[i] < H->Array[2 * i])
            maxPos = 2 * i;
        if(2 * i + 1 <= H->size && H->Array[maxPos] < H->Array[2 * i + 1])
            maxPos = 2 * i + 1;
        if(maxPos == i)
            break;

        swap_data(&H->Array[i], &H->Array[maxPos]);
    }
    return H->Array[0];
}

void HeapPrintf(pHeap H)
{
    int i;

    printf("Heap element: \n");
    for(i = 1; i < H->size; i++)
        printf("%d ", H->Array[i]);
    printf("\n");
}

int main(void)
{
    pHeap H = Heap_Create(100);
    Heap_Insert(H, 1);
    Heap_Insert(H, 2);
    Heap_Insert(H, 3);
    Heap_Insert(H, 4);
    Heap_Insert(H, 5);
    Heap_Insert(H, 6);
    Heap_Insert(H, 7);
    Heap_Insert(H, 8);
    Heap_Insert(H, 9);

    HeapPrintf(H);

    printf("Remove heap top: %d\n", Heap_RemoveTop(H));
    printf("Remove heap top: %d\n", Heap_RemoveTop(H));

    HeapPrintf(H);

    return 0;
}
