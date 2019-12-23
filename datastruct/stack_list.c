#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int

//StackNode是普通结点,pNode是指向普通结点的指针
struct StackNode{
    struct StackNode *next;
    ElementType Element;
};
typedef struct StackNode *pNode;

//StackHead是队列头结点,Stack是指向队列头的指针
struct StackHead{
    struct StackNode *top;
    int size;
};
typedef struct StackHead *Stack;

Stack Create(void)
{
    Stack S = malloc(sizeof(struct StackHead));

    if(S == NULL)
    {
        printf("Out of space!");
        return NULL;
    }
    
    S->top = NULL;
    S->size = 0;

    return S;
}

void Push(Stack S, ElementType x)
{
    pNode pTemp = malloc(sizeof(struct StackNode));
    if(pTemp == NULL)
        printf("Out of space!");
    else
    {
        pTemp->Element = x;

        pTemp->next = S->top;
        S->top = pTemp;
 
        S->size++;
    }
}

ElementType Pop(Stack S)
{
    if(S->size == 0)
        return (ElementType)NULL;

    ElementType ret = S->top->Element;
    pNode pTemp = S->top;
    S->top = pTemp->next;

    S->size--;
    free(pTemp);

    return ret;
}

bool BracketMatch(char str[])
{
    bool flag = true;
    int i;

    Stack S = Create();

    for(i = 0; str[i] != '\0' && flag == true; ++i)
    {
        switch (str[i])
        {
        case '(':
        case '[':
        case '{':
            Push(S, str[i]);
            break;
        case ')':
            if(S->size == 0 || Pop(S) != '(')
                flag = false;
            break;
        case ']':
            if(S->size == 0 || Pop(S) != '[')
                flag = false;
            break;
        case '}':
            if(S->size == 0 || Pop(S) != '{')
                flag = false;
            break;
        }
    }
    if(S->size == 0 && flag == true)
        return true;
    else
        return false;
}

int main(void)
{
    int i;

    Stack S = Create();

    for(i = 1; i < 9; i++)
    {
        Push(S, i * i);

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

    free(S);

    // BracketMatch function call code
    char str[100] = {0};

    printf("please input string:");
    scanf("%s", str);
    
    if(BracketMatch(str) == true)
        printf("Bracket match success.\n");
    else
        printf("Bracket match failed.\n"); 

    return 0;
}