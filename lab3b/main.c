#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

#include "structs.h"
#include "interface.h"
#include "menu.h"

#define MEM_FILE "mem.bin"
#define KEYS_FILE "savedata.bin"
#define VALUES_FILE "savevalues.bin"

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
    Table *t;
    if (table_init(&t, KEYS_FILE, VALUES_FILE, MEM_FILE) == ERR_CODE) {
        printf("One of .bin files does not exist\n(savedata.bin, savevalues.bin are required)\n");
        return ERR_CODE;
    }
    int code;

    while (inp != 0 || inp != -1) {
        switch (inp)
        {
        case 1:
            code = input_option(t);
            switch (code)
            {
            case ERR_CODE:
                printf("Error occurred while adding an element\n");
                break;
            case OVERFLOW:
                printf("Table overflow\n");
                break;
            case EOF:
                printf("Element input terminated\n");
                break;
            default:
                printf("Success\n");
                break;
            }
            break;
        case 2:
            code = delete_option(t);
            switch (code)
            {
            case ERR_CODE:
                printf("Error occurred while adding an element\n");
                break;
            case EOF:
                printf("Element input terminated\n");
                break;
            case NOT_FOUND:
                printf("There is no element with such key\n");
                break;
            default:
                printf("Success\n");
                break;
            }
            break;
        case 3:
            code = find_option(t);
            if (code == ERR_CODE) {
                printf("Error occurred while deleting an element\n");
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
            code = parse_file(t, inp);
            free(inp);
            if (code == ERR_CODE) {
                printf("Error occurred while importing from file. Table remains\n");
            } else {
                printf("Successfully imported from file\n");
            }
            printf("%d\n", t->max_len);
            break;
        case 6:
            code = delete_with_condition_option(t);
            switch (code)
            {
            case ERR_CODE:
                printf("Error occurred while adding an element\n");
                break;
            case EOF:
                printf("Element input terminated\n");
                break;
            case NOT_FOUND:
                printf("There is no element with such key\n");
                break;
            default:
                printf("Success\n");
                break;
            }
            break;
        case 7:
            code = find_children_option(t);
            switch (code)
            {
            case ERR_CODE:
                printf("Error occurred while finding children\n");
                break;
            case EOF:
                printf("Element input terminated\n");
                break;
            case NOT_FOUND:
                printf("There is no element with such key\n");
                break;
            default:
                break;
            }
            break;
        case -1:
            goto program_quit;
        case 0:
        {
            program_quit:
            save_table(t, KEYS_FILE, VALUES_FILE);
            free_table(t);
            return 0;
        }
        }
        inp = menu();
    }
    return 0;
}
