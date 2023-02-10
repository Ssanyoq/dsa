#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "mem.h"
#include "istream.h"

int min_index(int *arr, int len) {
    int min;
    int min_ind = -1;
    for (int i = 0; i < len; i++) {
        if (min_ind == -1) {
            min = arr[i];
            min_ind = i;
        } else if (arr[i] < min) {
            min = arr[i];
            min_ind = i;
        }
    }
    return min_ind;
}

int main() {
    int **arr;
    int n;
    int *m;
    printf("Input rows amount: ");
    if (input_u(&n) == -1) {
        return 1;
    }
    arr = (int **)safe_malloc(n * sizeof(int *));
    m = (int *)safe_malloc(n * sizeof(int));
    if (arr == NULL || m == NULL) {
        return 1;
    }
    printf("Input elements amount and then this amount of elements %d times: \n", n);
    for (int i = 0; i < n; i++) {
        if (input_u(&(m[i])) == -1) {
            return 1;
        }
        arr[i] = (int *)safe_malloc(m[i] * sizeof(int));
        for (int j = 0; j < m[i]; j++) {
            if (input_d(&(arr[i][j])) == -1) {
                return 1;
            }
        }
    }
    printf("\n\nGiven matrix:\n");
    print_arr(arr, n, m);

    for (int i = 0; i < n; i++) {
        int cur = min_index(arr[i], m[i]);
        arr[i] = &(arr[i][cur]);
        m[i] -= cur;
    }
    printf("\n\n");
    print_arr(arr, n, m);
    free_arr(arr, n);
    return 0;
}