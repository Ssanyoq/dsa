#include <stdio.h>

void print(int **arr, int n, int *m) {
    // prints an arr with n rows with
    // different sizes
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m[i]; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}