
// @EXPECTED_RESULTS@: CORRECT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define MAX_OPENING     20
#define MAX_BLOCKS      1000000
#define MAX_BLOCK_SIZE  100000000


int x, n;
int l1, l2;
int block[MAX_BLOCKS];


static int cmp(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return ia - ib;
}


int solve(void)
{
    int xnm = 10000000 * x;

    qsort(block, n, sizeof(block[0]), cmp);
    for (int i = 0; i < n && block[i] < xnm; i++) {
        l1 = block[i];
        l2 = xnm - l1;
        if (bsearch(&l2, block + i + 1, n - i - 1, sizeof(block[0]), cmp) != NULL)
            return 1;
    }

    return 0;
}


int main(void)
{
    while (scanf("%d", &x) == 1) {

        scanf("%d", &n);
        assert(x > 0 && x <= MAX_OPENING);
        assert(n >= 0 && n <= MAX_BLOCKS);
        for (int i = 0; i < n; i++) {
            scanf("%d", block + i);
            assert(block[i] > 0 && block[i] <= MAX_BLOCK_SIZE);
        }

        if (solve())
            printf("yes %d %d\n", l1, l2);
        else
            printf("danger\n");

    }

    return 0;
}

