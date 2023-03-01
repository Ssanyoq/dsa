#define ERR_CODE 1
#define CORRECT_CODE 0

typedef struct Item Item;
typedef struct Queue Queue;

int push(Queue *q, Item *val);

int pop(Queue *q, Item *val);

Item *check(Queue *q); // allows you to check 1st item without poping it

Queue *init(int len);

void print_queue(Queue *q);