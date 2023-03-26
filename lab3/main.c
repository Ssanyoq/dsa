#include "structs.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>

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
    printf("6 - Special Deletion\n");
    printf("7 - Find children\n");
    printf("\n0 - Quit\n");
    printf("Enter a number: ");
    char t;
    int inp;
    int out = scanf("%d%c", &inp, &t);
    while (out != 2 || t != '\n' || inp < 0 || inp > 7) {
        if (out == -1){
            return -1;
        }
        printf("Bad input, try again: ");
        scanf("%*[^\n]");
        out = scanf("%d%c", &inp, &t);
    }
    printf("---------------------------\n\n");
    if (out == -1) {
        return -1;
    }
    return inp;
}

int main() {
    int inp = menu();
    Table *t = (Table *)malloc(sizeof(Table));
    t->cur_size = 0;
    t->max_size = 0;
    t->elems = NULL;

    while (inp != 0 || inp != -1) {
        switch (inp)
        {
        case 1:
            printf("input as:\n<n>\n<key>\n<parent key>\n<Item>\n");
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            print_table(t);
            break;
        case 5:
            Table *out = parse_file("test.txt");
            if (out == NULL) {
                printf("Error occurred while importing from file. Table remains\n");
            } else {
                free(t);
                t = out;
                printf("Successfully imported from file\n");
            }
            break;
        case 6:
            break;
        case 7:
            break;
        case -1:
            return 0;
        }
        inp = menu();
    }
    return 0;
}