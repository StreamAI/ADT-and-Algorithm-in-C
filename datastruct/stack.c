#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int

struct StackHead{
    int capacity;
    int TopOfStack;
    int size;
    ElementType *Array;
};
typedef struct StackHead *Stack;

Stack Create(int capacity)
{
    Stack S = malloc(sizeof(struct StackHead));
    if(S == NULL)
    {
        printf("Out of space!");
        return NULL;
    }

    S->Array = malloc(capacity * sizeof(ElementType));
    if(S->Array == NULL)
        printf("Out of space!");

    S->capacity = capacity;
    S->TopOfStack = 0;
    S->size = 0;

    return S;
}

bool Push(Stack S, ElementType x)
{
    if(S->size == S->capacity)
        return false;
    
    S->Array[S->TopOfStack] = x;
    S->TopOfStack++;
    S->size++;

    return true;
}

ElementType Pop(Stack S)
{
    if(S->size == 0)
        return 0;

    ElementType ret = S->Array[S->TopOfStack - 1];
    S->TopOfStack--;
    S->size--;

    return ret;
}

void Destroy(Stack S)
{
    free(S->Array);
    free(S);
}

int main(void)
{
    int i;

    Stack S = Create(100);

    for(i = 1; i < 9; i++)
    {
        if(Push(S, i * i) == false)
        {
            printf("The stack is full.\n");
            break;
        }
        printf("%d ", i * i);
    }
    printf("\n");

    for(i = 1; i < 9; i++)
    {
        if(S->size == 0)
        {
            printf("The stack is empty.\n");
            break;
        }
        printf("%d ", Pop(S));
    }
    printf("\n");

    Destroy(S);

    return 0;
}