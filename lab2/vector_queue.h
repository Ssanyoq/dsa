typedef struct Item {
    char *id;
    int ta;
    int ts;
} Item;

typedef struct Queue
{
    struct Item *arr;
    int head;
    int tail;
    int max_size;
} Queue;

