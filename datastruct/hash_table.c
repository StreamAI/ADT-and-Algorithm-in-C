#include <stdio.h>
#include <stdlib.h>

#define ElementType int
typedef char *KeyType;
typedef unsigned int Index;

struct ListNode {
    struct ListNode *next;		//指向下一个元素的地址
    KeyType key;                //当前元素结点索引关键词
    ElementType Element;	    //可以是数据集合或其它的数据结构
};
typedef struct ListNode *pNode;

struct ListHead {
    struct ListNode *next;      //指向当前链表首结点地址
    int size;                   //当前链表元素节点数量
};
typedef struct ListHead *List;

struct HashTbl
{
    int TableSize;          //散列表容量
    List *HashLists;        //散列表数组基地址指针，指向各链表头地址
    int NodeCount;          //散列表当前元素节点数量
};
typedef struct HashTbl *HashTable;

Index Hash(const char *key, int TableSize)
{
	unsigned int HashVal = 0;
	while(*key != '\0')
	{
		HashVal = (HashVal << 5) + *key;
		key++;
	}
	return HashVal % TableSize;
}

HashTable HashInit(int TableSize)
{
    HashTable H;
    int i;
    // allocate hash table
    H = malloc(sizeof(struct HashTbl));
    if(H == NULL){
        printf("Out of space!");
        return NULL;
    }

    H->TableSize = TableSize;
    H->NodeCount = 0;
    // allocate array of lists
    H->HashLists = malloc((H->TableSize) * sizeof(List));
    if(H->HashLists == NULL){
        printf("Out of space!");
        return NULL;
    }
    // allocate list headers
    for(i = 0; i < H->TableSize; i++)
    {
        H->HashLists[i] = malloc(sizeof(struct ListHead));
        if(H->HashLists[i] == NULL){
            printf("Out of space!");
            return NULL;
        }

        H->HashLists[i]->size = 0;
        H->HashLists[i]->next = NULL;
    }
    return H;
}

pNode HashFind(HashTable H, KeyType key)
{
    List L = H->HashLists[Hash(key, H->TableSize)];
    pNode P = L->next;

    while (P != NULL && P->key != key)
        P = P->next;
    
    return P;
}

void HashInsert(HashTable H, KeyType key, ElementType data)
{
    pNode pos = HashFind(H, key);
    if(pos == NULL)
    {  
        pNode P = malloc(sizeof(struct ListNode));
        if(P == NULL){
            printf("Out of space!");
            return;
        }

        List L = H->HashLists[Hash(key, H->TableSize)];

        P->key = key;
        P->Element = data;
        P->next = L->next;
        L->next = P;

        L->size++;
        H->NodeCount++;
    }
}

void HashDelete(HashTable H, KeyType key)
{
    List L = H->HashLists[Hash(key, H->TableSize)];
    pNode prev = (pNode)L;
    while (prev->next != NULL && prev->next->key != key)
        prev = prev->next;
    
    if(prev->next != NULL)
    {
        List L = H->HashLists[Hash(key, H->TableSize)];
        pNode temp = prev->next;
        prev->next = temp->next;
        free(temp);
        
        L->size--;
        H->NodeCount--;
    }
}

HashTable ReHashDouble(HashTable H)
{
    HashTable OldHash = H;

    H = HashInit(2 * (OldHash->TableSize));

    int i;
    for(i = 0; i < OldHash->TableSize; i++)
    {
        List L = OldHash->HashLists[i];
        pNode P = L->next;
        while (P != NULL)
        {
            HashInsert(H, P->key, P->Element);
            pNode temp = P;
            P = P->next;
            free(temp);
        }
        free(L);
    }
    free(OldHash->HashLists);
    free(OldHash);

    return H;
}

void PrintHash(HashTable H)
{
    int i;
    printf("Hash table size: %d, base address: %X\n", H->TableSize, H->HashLists);
    for(i = 0; i < H->TableSize; i++)
    {
        List L = H->HashLists[i];
        pNode P = L->next;
        printf("HashTable[%d]: ", i);
        while (P != NULL)
        {
            if(P != L->next)
                printf("-->");
            printf("%d", P->Element);
            P = P->next;
        }
        printf("\n");
    }
}

int main(void)
{
    HashTable H = HashInit(3);
    
    HashInsert(H, "key1", 1);
    HashInsert(H, "key2", 2);
    HashInsert(H, "key3", 3);
    HashInsert(H, "key4", 4);
    HashInsert(H, "key5", 5);
    HashInsert(H, "key6", 6);
    PrintHash(H);

    if(H->NodeCount > H->TableSize)
        H = ReHashDouble(H);
    PrintHash(H);

    KeyType key = "key3";
    pNode ptr = HashFind(H, key);
    if(ptr != NULL)
        printf("find %s data: %d\n", key, ptr->Element);

    HashDelete(H, "key1");
    HashDelete(H, "key5");
    PrintHash(H);

    return 0;
}