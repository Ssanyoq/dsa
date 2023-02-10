#include <stdlib.h>
#include <stdio.h>

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        printf("Error occurred while allocating memory\n");
        return NULL;
    }
    return ptr;
}

void free_arr(int **arr, int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
}