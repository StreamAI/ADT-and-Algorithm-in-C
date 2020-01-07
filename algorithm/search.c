#include <stdlib.h>
#include <stdio.h>
 
struct data{
    int nr;
    char *value;
} dat[] = {
    {1, "Foo"}, {2, "Bar"}, {3, "Hello"}, {4, "World"}
};

int seq[] = {0, 1, 1, 2, 2, 3, 3, 3, 5, 8, 9};

void swap_data(int *a, int *b)
{
    if(*a != *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

int partition(int *data, int left, int right)
{
    /*
    // 随机选择分界线或枢纽值
    int index = left + rand() % (right - left + 1);
    swap_data(&data[index], &data[right]);
    int i = left, j = right - 1, pivot = right;
    */
    // 三数取中法选择分界线或枢纽值
    int mid = left + (right - left) / 2;
    if(data[left] > data[mid])
        swap_data(&data[left], &data[mid]);
    if(data[left] > data[right])
        swap_data(&data[left], &data[right]);
    if(data[mid] > data[right])
        swap_data(&data[mid], &data[right]);

    swap_data(&data[mid], &data[right-1]);
    int i = left + 1, j = right - 2, pivot = right - 1;
    
    while (1)
    {
        while (data[i] < data[pivot])
            i++;

        while (j > left && data[j] >= data[pivot])
            j--;
        
        if(i < j)
            swap_data(&data[i], &data[j]);
        else
            break;
    }
    
    if(i < right)
        swap_data(&data[i], &data[pivot]);

    return i;
}

int binary_search(int *data, int left, int right, int target)
{
    if(left > right || target < data[left] || target > data[right])
        return -1;
    if(left == right)
    {
        if(target == data[left])
            return left;
        else
            return -1;
    }

    int mid = left + (right - left) / 2;
    if(target <= data[mid])
        return binary_search(data, left, mid, target);
    else if(target > data[mid])
        return binary_search(data, mid + 1, right, target);
}

int searth_Kth(int *data, int left, int right, int k)
{
    if(right - left <= 1)
    {
        if(right - left == 1 && data[left] > data[right])
            swap_data(&data[left], &data[right]);
        
        if(left == k - 1)
            return data[left];
        else if(right == k - 1)
            return data[right];
        else
            return -1;
    }

    int divide = partition(data, left, right);

    if(divide > k - 1)
        return searth_Kth(data, left, divide - 1, k);
    else if(divide < k - 1)
        return searth_Kth(data, divide + 1, right, k);
    else
        return data[k - 1];
}
 
int data_cmp(const void *lhs, const void *rhs) 
{
    const struct data *const l = (const struct data *)lhs;
    const struct data *const r = (const struct data *)rhs;
 
    if (l->nr < r->nr)
        return -1;
    else if (l->nr > r->nr)
        return 1;
    else
        return 0;
}
 
int main(void) 
{
    int k;

    printf("binary search: 1\n");
    printf("search Kth   : 2\n");
    printf("bsearch      : 3\n");
    printf("Select method: ");
    scanf("%d", &k);

    switch (k)
    {
    case 1:
    {
        int target = 3;
        int res1 = binary_search(seq, 0, sizeof(seq) / sizeof(seq[0]) - 1, target);
        if(res1 != -1)
            printf("\nFound seq[%d]: %d\n", res1, seq[res1]);
        else
            printf("\nTarget %d not found\n", target);
        break;
    }
    case 2:
    {
        int kth = 3;
        int res1 = searth_Kth(seq, 0, sizeof(seq) / sizeof(seq[0]) - 1, kth);
        if(res1 != -1)
            printf("\nFound seq[%d]: %d\n", kth, res1);
        else
            printf("\nKth %d not found\n", kth);
        break;
    }
    case 3:
    {
        struct data key = { .nr = 3 };
        struct data const *res2 = bsearch(&key, dat, sizeof(dat) / sizeof(dat[0]),
                                            sizeof(dat[0]), data_cmp);
        if(res2)
            printf("\nNo %d: %s\n", res2->nr, res2->value);
        else
            printf("\nNo %d not found\n", key.nr);
        break;
    }
    default:
        break;
    }
    
    return 0;
}