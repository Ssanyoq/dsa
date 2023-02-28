typedef struct Item {
    char *id;
    int ta;
    int ts;
    Item *next;
} Item;

typedef struct Stack
{
    Item *top;
} Stack;