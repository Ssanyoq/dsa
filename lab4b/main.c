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
    printf("3 - Print tree\n");
    printf("4 - Find node\n");
    printf("5 - Special find\n");
    printf("6 - Import tree from file\n");
    printf("7 - Pretty print the tree\n");
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
    Node *root = NULL;
    int code;
    while (inp != EOF) {
        switch (inp)
        {
        case 1:
            code = insert_opt(&root);
            break;
        case 2:
            code = delete_opt(&root);
            break;
        case 3:
            print_tree_opt(root);
            code = SUCCESS;
            break;
        case 4:
            code = find_opt(root);
            break;
        case 5:
            code = spec_find_opt(root);
            break;
        case 6:
            code = import_opt(&root);
            printf("%p\n", root);
            break;
        case 7:
            put_tree(root, 0);
            code = SUCCESS;
            break;
        case -1:
            goto program_quit;
        case 0:
            program_quit:
            free_tree(root);
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
    free_tree(root);
    return 0;
}
