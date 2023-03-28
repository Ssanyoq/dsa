#include "structs.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

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
    int code;

    while (inp != 0 || inp != -1) {
        switch (inp)
        {
        case 1:
            code = input_elem(stdin, t);
            if (code == ERR_CODE) {
                printf("Error occured while adding an element\n");
            } else {
                printf("Success\n");
            }
            break;
        case 2:
            code = delete_elem(t);
            if (code == ERR_CODE) {
                printf("Error occured while deleting an element\n");
            } else {
                printf("Success\n");
            }
            break;
        case 3:
            code = find_with_inputs(t);
            if (code == ERR_CODE) {
                printf("Error occured while deleting an element\n");
            } else {
                // printf("Success\n");
            }
            break;
        case 4:
            print_table(t);
            break;
        case 5:
            printf("Input relative path to a desired import file: ");
            char *inp = readline("");
            if (inp == NULL) {
                goto program_quit;
            }
            Table *out = parse_file(inp);
            free(inp);
            if (out == NULL) {
                printf("Error occurred while importing from file. Table remains\n");
            } else {
                free(t);
                t = out;
                printf("Successfully imported from file\n");
            }
            break;
        case 6:
            code = delete_with_conditions(t);
            if (code == ERR_CODE) {
                printf("Error occured while deleting an element\n");
            }
            break;
        case 7:
            code = find_children_prints(t);
            if (code == ERR_CODE) {
                printf("Error occured while finding children\n");
            }
            break;
        case -1:
            goto program_quit;
        case 0:
            program_quit:
            free_table(t);
            return 0;
        }
        inp = menu();
    }
    return 0;
}