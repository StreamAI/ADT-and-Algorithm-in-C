#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int

//QueueNode是普通结点,pNode是指向普通结点的指针
struct QueueNode{
    struct QueueNode *next;
    ElementType Element;
};
typedef struct QueueNode *pNode;

//QueueHead是队列头结点,Queue是指向队列头的指针
struct QueueHead{
    struct QueueNode *head;
    struct QueueNode *tail;
    int size;
};
typedef struct QueueHead *Queue;

Queue Create(void)
{
    Queue Q = malloc(sizeof(struct QueueHead));

    if(Q == NULL)
    {
        printf("Out of space!");
        return NULL;
    }
    
    Q->head = NULL;
    Q->tail = NULL;
    Q->size = 0;

    return Q;
}

void Enqueue(Queue Q, ElementType x)
{
    pNode pTemp = malloc(sizeof(struct QueueNode));
    if(pTemp == NULL)
        printf("Out of space!");
    else
    {
        pTemp->Element = x;
        pTemp->next = NULL;

        if(Q->size == 0)
        {
            Q->head = pTemp;
            Q->tail = pTemp;
        }else{
            Q->tail->next = pTemp;
            Q->tail = pTemp;
        }    
        Q->size++;
    }
}

ElementType Dequeue(Queue Q)
{
    if(Q->head == NULL)
        return (ElementType)NULL;

    ElementType ret = Q->head->Element;
    pNode pTemp = Q->head;
    Q->head = pTemp->next;

    Q->size--;
    free(pTemp);

    return ret;
}

void printQueue(Queue Q)
{
    pNode ptr = Q->head;

    printf("Queue has %d elements: ", Q->size);
    while(ptr != NULL)
    {
        if(ptr != Q->head)
            printf(" --> ");

        printf("%d", ptr->Element);
        ptr = ptr->next;
    }
    printf("\n\n");
}

int main(void)
{
    int i;

    Queue Q = Create();

    for(i = 1; i < 9; i++)
        Enqueue(Q, i * i);
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

    free(Q);

    return 0;
}