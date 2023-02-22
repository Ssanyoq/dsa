typedef struct Item Item;
typedef struct Stack Stack;

int push(Stack *s, Item *val);

int pop(Stack *s, Item *val);

Stack *init(int len);