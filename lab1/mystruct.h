#ifndef MYSTRUCT_H
#define MYSTRUCT_H

typedef struct 
{
    List *next;
    int value;
} List;


typedef struct
{
    int size;
    List *head;
} Matrix;

#endif
