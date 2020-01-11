#include <stdio.h>
#include <stdlib.h>

#define DataType int
#define max(a, b)   ((a) > (b)) ? (a) : (b)

struct BinaryTree_Node{
    DataType                data;
    struct BinaryTree_Node *LeftChild;
    struct BinaryTree_Node *RightChild;
    int                     height;
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
            T = T->LeftChild ? T->LeftChild : T->RightChild;
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

int getHeight(pTreeNode T)
{
    if(T == NULL)
        return 0;

    return T->height;
}

int getBalanceFactor(pTreeNode T)
{   
    if(T == NULL)
        return 0;

    return getHeight(T->LeftChild) - getHeight(T->RightChild);
}

void updateHeight(pTreeNode T)
{
    if(T == NULL)
        return;
    
    T->height = max(getHeight(T->LeftChild), getHeight(T->RightChild)) + 1;
}

pTreeNode LeftRotation(pTreeNode T)
{
    pTreeNode temp = T->RightChild;
    T->RightChild = temp->LeftChild;
    temp->LeftChild = T;

    updateHeight(T);
    updateHeight(temp);

    return temp;
}

pTreeNode RightRotation(pTreeNode T)
{
    pTreeNode temp = T->LeftChild;
    T->LeftChild = temp->RightChild;
    temp->RightChild = T;

    updateHeight(T);
    updateHeight(temp);

    return temp;
}

pTreeNode TreeRebalance(pTreeNode T)
{
    if(T == NULL)
        return NULL;
    
    updateHeight(T);
    int fb_root = getBalanceFactor(T);
    int fb_left = getBalanceFactor(T->LeftChild);
    int fb_right = getBalanceFactor(T->RightChild);
	// LL型
    if(fb_root > 1 && fb_left > 0)
        return RightRotation(T);
    // LR型
    else if(fb_root > 1 && fb_left < 0){
        T->LeftChild = LeftRotation(T->LeftChild);
        return RightRotation(T);
     // RR型
    }else if(fb_root < -1 && fb_right < 0)
        return LeftRotation(T);
    // RL型
    else if(fb_root < -1 && fb_right > 0){
        T->RightChild = RightRotation(T->RightChild);
        return LeftRotation(T);
    }else
        return T;
}

pTreeNode AVL_Insert(pTreeNode T, DataType x)
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
            T->height = 1;
        }
        return T;
    }

    if(x < T->data)
        T->LeftChild = AVL_Insert(T->LeftChild, x);
    else if(x > T->data)
        T->RightChild = AVL_Insert(T->RightChild, x);    
    // else x is in the tree already, we will do nothing
    
    T = TreeRebalance(T);
    return T;
}

int main(void)
{
    pTreeNode T = NULL, tmp = NULL;

    T = Insert(T, 16);
    T = Insert(T, 18);  
    T = Insert(T, 13);
    T = Insert(T, 17);
    T = Insert(T, 15);
    T = Insert(T, 25);
    T = Insert(T, 27);

    printf("\nBinary search tree:\n");
    printf("preOrder: ");
    preOrder(T);
    printf("\n");
    printf("inOrder: "); 
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

    T = Delete(T, 27);
    T = Delete(T, 13);
    T = Delete(T, 18);

    printf("preOrder: ");
    preOrder(T);
    printf("\n");
    printf("inOrder: "); 
    inOrder(T);
    printf("\n");
    printf("postOrder: ");
    postOrder(T);
    printf("\n");

    pTreeNode T_AVL = NULL;

    T_AVL = AVL_Insert(T_AVL, 1);
    T_AVL = AVL_Insert(T_AVL, 2);
    T_AVL = AVL_Insert(T_AVL, 3);
    T_AVL = AVL_Insert(T_AVL, 4);
    T_AVL = AVL_Insert(T_AVL, 5);
    T_AVL = AVL_Insert(T_AVL, 6);
    T_AVL = AVL_Insert(T_AVL, 7);
    T_AVL = AVL_Insert(T_AVL, 8);
    T_AVL = AVL_Insert(T_AVL, 9);

    printf("\nAVL balanced tree:\n");
    printf("preOrder: ");
    preOrder(T_AVL);
    printf("\n");
    printf("inOrder: "); 
    inOrder(T_AVL);
    printf("\n");
    printf("postOrder: ");
    postOrder(T_AVL);
    printf("\n");

    return 0;
}