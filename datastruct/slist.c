#include <stdio.h>
#include <stdlib.h>

#define ElementType     int

//Node是普通结点,pNode是指向普通结点的指针
struct Node {
    struct Node *next;
    ElementType Element;
};
typedef struct Node *pNode;

//HeadNode特用于头结点，List也只能指向头结点
struct HeadNode {
    struct Node *next;
    int size;
};
typedef struct HeadNode *List;


List Create(void)
{
    List ptr = malloc(sizeof(struct HeadNode));
	if(ptr == NULL)
        printf("Out of space!");
    
    ptr->size = 0;
    ptr->next = NULL;

    return ptr;
}

pNode Find(List L, ElementType x)
{
    pNode ptr = L->next;

    while (ptr != NULL && ptr->Element != x)
        ptr = ptr->next;
    
    return ptr;
}

void Insert(List L, pNode Position, ElementType x)
{
    pNode pTemp = malloc(sizeof(struct Node));
    if(pTemp == NULL)
        printf("Out of space!");

    pTemp->Element = x;
    if(Position != NULL)
    {
        pTemp->next = Position->next;
        Position->next = pTemp;
        
        L->size++;
    }
}

void Delete(List L, ElementType x)
{
    pNode Prev = (pNode) L;

    while (Prev->next != NULL && Prev->next->Element != x)
        Prev = Prev->next;
    
    if(Prev->next != NULL)
    {
        pNode pTemp = Prev->next;
        Prev->next = pTemp->next;
        free(pTemp);
        
        L->size--;
    }
}


void PrintList(List L)
{
    pNode ptr = L->next;

    printf("List has %d elements: ", L->size);
    while(ptr != NULL)
    {
        if(ptr != L->next)
            printf(" --> ");

        printf("%d", ptr->Element);
        ptr = ptr->next;
    }
    printf("\n");
}

void ReverseList(List L)
{
    if(L->next == NULL || L == NULL)
        return;

    pNode P = L->next;
    pNode T = NULL;

    while(P->next != NULL)
    {
        T = P->next;
        P->next = T->next;
        T->next = L->next;
        L->next = T;
        PrintList(L);
    }
}

pNode ReverseList_Recursive(List L, pNode first)
{
    if(first->next == NULL || first == NULL)
    {
        L->next = first;
        return first;
    }

    pNode T = ReverseList_Recursive(L, first->next);

    T->next = first;
    first->next = NULL;

    PrintList(L);
    return first;
}

void SortList(List L)
{
    if(L->next == NULL || L == NULL)
        return;

    pNode P = L->next;
    pNode T = NULL;

    while(P->next != NULL)
    {
        T = P->next;

        if(T->Element >= P->Element)
            P = T;
        else
        {
            P->next = T->next;

            pNode Cur = (pNode) L;
            while(Cur->next != P->next && Cur->next->Element < T->Element)
                Cur = Cur->next;
            
            T->next = Cur->next;
            Cur->next = T;
        }
        PrintList(L);
    }
}

int main(void)
{
    List L = Create();
    pNode Position  = (pNode) L;

    Insert(L, Position, 1);
    Insert(L, Position, 3);
    Insert(L, Position, 4);
    PrintList(L);

    Position = Find(L, 1);
    if (Position != NULL)
    {
        Insert(L, Position, 7);
        Insert(L, Position, 8);
    }
    PrintList(L);
    printf("\n");
    
    ReverseList(L);
    PrintList(L);
    printf("\n");
    
    SortList(L);
    PrintList(L);
    printf("\n");
    
    ReverseList_Recursive(L, L->next);
    PrintList(L);
    printf("\n");

    Delete(L, 7);
    Delete(L, 4);
    PrintList(L);
    printf("\n");
    
    return 0;
}