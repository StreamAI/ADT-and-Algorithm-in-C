#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int

struct QueueHead{
    int capacity;
    int head;
    int tail;
    int size;
    ElementType *Array;
};
typedef struct QueueHead *Queue;

Queue Create(int capacity)
{
    Queue Q = malloc(sizeof(struct QueueHead));
    if(Q == NULL)
    {
        printf("Out of space!");
        return NULL;
    }

    Q->Array = malloc(capacity * sizeof(ElementType));
    if(Q->Array == NULL)
        printf("Out of space!");

    Q->capacity = capacity;
    Q->head = 0;
    Q->tail = 0;
    Q->size = 0;

    return Q;
}

bool Enqueue(Queue Q, ElementType x)
{
    if((Q->tail + 1)%Q->capacity == Q->head)
        return false;
    
    Q->Array[Q->tail] = x;
    Q->tail = (Q->tail + 1) % Q->capacity;
    Q->size++;

    return true;
}

ElementType Dequeue(Queue Q)
{
    if(Q->head == Q->tail)
        return (ElementType)NULL;

    ElementType ret = Q->Array[Q->head];
    Q->head = (Q->head + 1) % Q->capacity;
    Q->size--;

    return ret;
}

void Destroy(Queue Q)
{
    free(Q->Array);
    free(Q);
}

void printQueue(Queue Q)
{
    printf("Queue has %d elements: ", Q->size);
    int i = Q->head;
    while(i != Q->tail)
    {
        if(i != Q->head)
            printf(" ");
        printf("%d", Q->Array[i]);
        i = (i + 1) % Q->capacity;
    }
    printf("\n\n");
}

int main(void)
{
    int i;

    Queue Q = Create(100);

    for(i = 1; i < 9; i++)
    {
        if(Enqueue(Q, i * i) == false)
        {
            printf("The queue is full.\n");
            break;
        }
    }
    printf("\n");
    printQueue(Q);

    for(i = 1; i < 7; i++)
    {
        if(Q->size == 0)
        {
            printf("The queue is empty.\n");
            break;
        }
        printf("%d ", Dequeue(Q));
    }
    printf("\n");
    printQueue(Q);

    Destroy(Q);

    return 0;
}