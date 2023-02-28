#define ERR_CODE 1
#define CORRECT_CODE 0

typedef struct Item Item;
typedef struct Queue Queue;

int push(Queue *q, Item *val);

int pop(Queue *q, Item *val);

Queue *init(int len);