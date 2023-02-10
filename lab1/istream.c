#include <stdio.h>

void clear_buff() {
    scanf("%*[^\n]");
}

int input_d(int *var) {
    // doesn't clear anything
    char t;
    int inp;
    int out = scanf("%d%c", &inp, &t);
    while (out != 2 || t != '\n') {
        if (out == -1){
            return -1;
        }
        printf("Bad input, try again: ");
        clear_buff();
        out = scanf("%d%c", &inp, &t);
    }
    *var = inp;
    return 0;
}

int input_u(int *var) { 
    int out = input_d(var);
    if (out == -1) { 
        return -1;
    }
    while (*var < 0)
    {
        printf("Bad input, try again: ");
        out = input_d(var);
        if (out == -1) {
            return -1;
        }
    }
    return 0;
    
}