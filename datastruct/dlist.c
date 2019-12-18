#include <stdio.h>
#include <stdlib.h>

#define ElementType     int

//Node是普通结点,pNode是指向普通结点的指针
struct Node {
	struct Node *next;		//指向下一个元素的地址
    ElementType Element;	//可以是数据集合或其它的数据结构
    struct Node *prev;		//指向前一个元素的地址   
};
typedef struct Node *pNode;

//HeadNode特用于头结点，List也只能指向头结点
struct HeadNode {
    struct Node *next;		//指向第一个结点的地址
    int size;				//保存链表中有效元素数目
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
        if(Position->next == NULL)
        {
            Position->next = pTemp;
            pTemp->next = NULL;
            pTemp->prev = Position;
        } else {
            Position->next->prev = pTemp;
            pTemp->next = Position->next;
            Position->next = pTemp;
            pTemp->prev = Position;
        }
        L->size++;
    }
}

void Delete(List L, ElementType x)
{
    pNode pTemp = Find(L, x);
    
    if(pTemp != NULL)
    {
        if(pTemp->next == NULL)
        {
            pTemp->prev->next = NULL;
        } else {
            pTemp->next->prev = pTemp->prev;
            pTemp->prev->next = pTemp->next;
        }
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
            printf(" <--> ");

        printf("%d", ptr->Element);
        ptr = ptr->next;
    }
    printf("\n");
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

    Delete(L, 7);
    Delete(L, 4);
    PrintList(L);
 
    return 0;
}