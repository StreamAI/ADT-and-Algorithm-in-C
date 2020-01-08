#include <stdio.h>
#include <stdlib.h>

#define DataType int

struct BinaryTree_Node{
    DataType                data;
    struct BinaryTree_Node *LeftChild;
    struct BinaryTree_Node *RightChild;
};
typedef struct BinaryTree_Node   *pTreeNode;

pTreeNode Find(pTreeNode T, DataType x)
{
    if(T == NULL)
        return NULL;

    if(x < T->data)
        return Find(T->LeftChild, x);
    else if(x > T->data)
        return Find(T->RightChild, x);
    else
        return T;
}

pTreeNode FindMin(pTreeNode T)
{
    if(T == NULL)
        return NULL;
    
    if(T->LeftChild == NULL)
        return T;
    else
        return FindMin(T->LeftChild);
}

pTreeNode FindMax(pTreeNode T)
{
    if(T != NULL)
        while(T->RightChild != NULL)
            T = T->RightChild;

    return T;
}

pTreeNode Insert(pTreeNode T, DataType x)
{
    if(T == NULL)
    {
        // create and return a one-node tree
        T = malloc(sizeof(struct BinaryTree_Node));
        if(T == NULL){
            printf("Out of space!");
        }else{
            T->data = x;
            T->LeftChild = T->RightChild = NULL;
        }
        return T;
    }

    if(x < T->data)
        T->LeftChild = Insert(T->LeftChild, x);
    else if(x > T->data)
        T->RightChild = Insert(T->RightChild, x);    
    // else x is in the tree already, we will do nothing

    return T;
}

pTreeNode Delete(pTreeNode T, DataType x)
{
    if(T == NULL)
    {
        printf("Element not found");
        return NULL;
    }

    if(x < T->data)
        T->LeftChild = Delete(T->LeftChild, x);
    else if(x > T->data)
        T->RightChild = Delete(T->RightChild, x);
    // found target element to delete
    else
    {
        pTreeNode tmp;
        // have two children
        if(T->LeftChild && T->RightChild)
        {
            // replace with samllest in right subtree
            tmp = FindMin(T->RightChild);
            T->data = tmp->data;
            T->RightChild = Delete(T->RightChild, T->data);
        }else{
            // one or zero children
            tmp = T;
            if(T->LeftChild == NULL)
                T = T->RightChild;
            else if(T->RightChild == NULL)
                T = T->LeftChild;

            free(tmp);
        }
    }
    
    return T;
}

void preOrder(pTreeNode T)
{  
	if (T == NULL) 
		return;
		  
	printf("%d ", T->data);
	preOrder(T->LeftChild);  
	preOrder(T->RightChild);
}

void inOrder(pTreeNode T) 
{  
	if (T == NULL) 
		return;
		  
	inOrder(T->LeftChild);  
	printf("%d ", T->data);
	inOrder(T->RightChild);
}

void postOrder(pTreeNode T) 
{  
	if (T == NULL) 
		return;
	
	postOrder(T->LeftChild);  
	postOrder(T->RightChild);  
	printf("%d ", T->data);
}

int main(void)
{
    pTreeNode T = NULL, tmp = NULL;

    T = Insert(T, 16);
    Insert(T, 18);  
    Insert(T, 13);
    Insert(T, 17);
    Insert(T, 15);
    Insert(T, 25);
    Insert(T, 27);
    Insert(T, 19);

    printf("preOrder: ");
    preOrder(T);
    printf("\n");
    printf("inOrder: "); 
    inOrder(T);
    printf("\n");
    printf("postOrder: ");
    postOrder(T);
    printf("\n");

    tmp = Find(T, 18);
    printf("find target result: %d\n", tmp->data);
    tmp = FindMin(T);
    printf("find min result: %d\n", tmp->data);
    tmp = FindMax(T);
    printf("find max result: %d\n", tmp->data);

    Delete(T, 27);
    Delete(T, 13);
    Delete(T, 18);

    printf("preOrder: ");
    preOrder(T);
    printf("\n");
    printf("inOrder: "); 
    inOrder(T);
    printf("\n");
    printf("postOrder: ");
    postOrder(T);
    printf("\n");

    return 0;
}