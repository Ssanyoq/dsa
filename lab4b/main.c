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