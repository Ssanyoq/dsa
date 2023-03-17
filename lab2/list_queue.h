typedef struct Item {
    char *id;
    int ta;
    int ts;
    struct Item *next;
} Item;

typedef struct Queue
{
    Item *tail;
    Item *head;
} Queue;