typedef struct Item {
    char *id;
    int ta;
    int ts;
} Item;

typedef struct Stack
{
    Item *arr;
    int top;
    int max_size;
} Stack;

