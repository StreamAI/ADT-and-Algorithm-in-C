#include <stdlib.h>
#include <stdio.h>
 
struct data{
    int nr;
    char *value;
} dat[] = {
    {1, "Foo"}, {2, "Bar"}, {3, "Hello"}, {4, "World"}
};

int seq[] = {0, 1, 1, 2, 2, 3, 3, 3, 5, 8, 9};

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
    printf("bsearch      : 2\n");
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