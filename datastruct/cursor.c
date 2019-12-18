#include <stdio.h>

#define ElementType     int
#define SpaceSize       100

//Node是普通结点,pNode是指向普通结点的指针
struct Node {
    ElementType Element;	//元素数据类型
    int next;				//指向下一个数组元素的下标
};

struct Node CursorSpace[SpaceSize];	//为游标数组分配的线性连续地址空间

typedef int List;           //为游标数组模拟的链表头游标定义一个类型别名

void Init(void)
{
    for (int i = 0; i < SpaceSize - 1; ++i)
        CursorSpace[i].next = i + 1;

    CursorSpace[SpaceSize - 1].next = 0;
}

int CursorAlloc(void)
{
    int pos = CursorSpace[0].next;

    CursorSpace[0].next = CursorSpace[pos].next;

    return pos;
}

void CursorFree(int pos)
{
    CursorSpace[pos].next = CursorSpace[0].next;
    CursorSpace[0].next = pos;
}

List Create(void)
{
    List pos = CursorAlloc();
    if(pos == 0)
        printf("Out of space!");

    CursorSpace[pos].Element = 0;
    CursorSpace[pos].next = 0;

    return pos;
}

int Find(List L, ElementType x)
{
    int pos = CursorSpace[L].next;

    while (pos != 0 && CursorSpace[pos].Element != x)
        pos = CursorSpace[pos].next;
    
    return pos;
}

void Insert(List L, int Position, ElementType x)
{
    int pos = CursorAlloc();
    if(pos == 0)
        printf("Out of space!");

    CursorSpace[pos].Element = x;
    if(Position != 0)
    {
        CursorSpace[pos].next = CursorSpace[Position].next;
        CursorSpace[Position].next = pos;

        CursorSpace[L].Element++;
    }
}

void Delete(List L, ElementType x)
{
    int prev = L;

    while (CursorSpace[prev].next != 0 && CursorSpace[CursorSpace[prev].next].Element != x)
        prev = CursorSpace[prev].next;
    
    if(CursorSpace[prev].next != 0)
    {
        int pos = CursorSpace[prev].next;
        CursorSpace[prev].next = CursorSpace[pos].next;
        CursorFree(pos);

        CursorSpace[L].Element--;
    }
}

void PrintList(List L)
{
    int pos = CursorSpace[L].next;

    printf("List has %d elements: ", CursorSpace[L].Element);
    while(pos != 0)
    {
        if(pos != CursorSpace[L].next)
            printf(" --> ");

        printf("%d", CursorSpace[pos].Element);
        pos = CursorSpace[pos].next;
    }
    printf("\n");
}

int main(void)
{
    Init();

    List L = Create();
    int Position = L;

    Insert(L, Position, 1);
    Insert(L, Position, 3);
    Insert(L, Position, 4);
    PrintList(L);

    Position = Find(L, 1);
    if (Position != 0)
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