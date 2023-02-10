#ifndef MEM_H
#define MEM_H

#include <stddef.h>

void *safe_malloc(size_t size);

void free_arr(int **arr, int n);

#endif