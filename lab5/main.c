#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "interface.h"
#include "structs.h"
#include "menu.h"

#define LIMIT 1000

int menu() {
    // -1: EOF
    // 0-7: Option has been chosen
    printf("---------------------------\n");
    printf("Choose option: \n");
    printf("1 - Traversal (DFS++)\n");
    printf("2 - Find shortest path\n");
    printf("3 - Special option\n");
    printf("4 - Add vertex\n");
    printf("5 - Add edge\n");
    printf("6 - Delete vertex\n");
    printf("7 - Delete edge\n");
    printf("8 - Rename vertex\n");
    printf("9 - Change edge\n");
    printf("10 - Print the graph\n");
    printf("\n0 - Quit program\n");
    char t;
    int inp;
    int out = scanf("%d%c", &inp, &t);
    while (out != 2 || t != '\n' || inp < 0 || inp > 10) {
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
    Graph *g = malloc(sizeof(Graph));
    g->vertices = malloc(LIMIT * sizeof(Vertex));
    g->max_len = LIMIT;
    g->len = 0;
    int code;
    while (inp != EOF) {
        switch (inp)
        {
        case 1: // DFS
            code = traverse(g);
            break;
        case 2: // shortest path
            code = shortest_opt(g);
            break;
        case 3: // Special
            code = special_opt(g);
            break;
        case 4: // Add vertex
            code = add_vertex_opt(g);
            break;
        case 5: // Add edge
            code = add_edge_opt(g);
            break;
        case 6: // Delete vertex
            code = delete_vertex_opt(g);
            break;
        case 7: // Delete edge
            code = delete_edge_opt(g);
            break;
        case 8: // Change vertex
            code = rename_vertex_opt(g);
            break;
        case 9: // Change edge
            code = change_edge_opt(g);
            break;
        case 10: // Print
            print_graph(g);
            code = SUCCESS;
            break;
        case -1:
            goto program_quit;
        case 0:
            program_quit:
            free_graph(g);
            return 0;
        }
        switch (code)
        {
        case SUCCESS:
            printf("Success\n");
            break;
        case NOT_FOUND:
            printf("Vertex or edge not found\n");
            break;
        case ERR:
            printf("Error occurred\n");
            break;
        case ALREADY_EXISTS:
            printf("Inputted name or edge already exists\n");
            break;
        case OVERFLOW:
            printf("Not enough memory allocated for new element\n");
            break;
        default:
            break;
        }
        inp = menu();
    }
    free_graph(g);
    return 0;
}
