#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "mem.h"

int main() {
    int **arr;
    int n;
    int *m;
    printf("Input rows amount: ");
    scanf("%d", &n);
    arr = (int **)safe_malloc(n * sizeof(int *));
    m = (int *)safe_malloc(n * sizeof(int));
    if (arr == NULL || m == NULL) {
        return 1;
    }
    printf("Input elements amount and then this amount of elements %d times: \n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &(m[i]));
        arr[i] = (int *)safe_malloc(m[i] * sizeof(int));
        for (int j = 0; j < m[i]; j++) {
            scanf("%d", &(arr[i][j]));
        }
    }
    printf("\n\n");
    print_arr(arr, n, m);

    return 0;
}