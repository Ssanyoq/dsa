#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "interface.h"
#include "structs.h"

int menu() {
    // -1: EOF
    // 0-7: Option has been chosen
    printf("---------------------------\n");
    printf("Choose option: \n");
    printf("1 - Add element\n");
    printf("2 - Delete element\n");
    printf("3 - Find element\n");
    printf("4 - Print out table\n");
    printf("5 - Import from text file\n");
    // TODO:
    return 1;
}

int main() {
    Table *t = table_init(20);
    insert(t, "haksjdkhaskjdhello", "world");
    print_table(t);
}