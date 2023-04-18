#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "interface.h"
#include "structs.h"
#include "menu.h"

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
    printf("\n0 - Quit program\n");
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
    if (out == EOF) {
        return EOF;
    }
    return inp;
}

int main() {
    int inp = menu();
    Table *t = table_init(0);
    int code;
    while (inp != EOF) {
        switch (inp)
        {
        case 1:
            code = insert_opt(t);
            break;
        case 2:
            code = delete_opt(t);
            break;
        case 3:
            code = find_opt(t);
            break;
        case 4:
            print_table(t);
            code = SUCCESS;
            break;
        case 5:
            code = import_table_opt(&t);
            break;
        case -1:
            goto program_quit;
        case 0:
            program_quit:
            free_table(t);
            return 0;
        }
        switch (code)
        {
        case SUCCESS:
            printf("Success\n");
            break;
        case NOT_FOUND:
            printf("Element not found\n");
            break;
        case TABLE_OVERFLOW:
            printf("Not enough space for new element\n");
            break;
        case ERR:
            printf("Error occurred\n");
            break;
        case ALREADY_EXISTS:
            printf("Inputted element already exists\n");
            break;
        default:
            break;
        }
        inp = menu();
    }
    return 0;
}