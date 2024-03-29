#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include "interface.h"

int input_d(int *out) {
    char t;
    int code = scanf("%d%c", out, &t);
    while (code != 2 || t != '\n') {
        if (code == EOF) {
            return EOF;
        }
        printf("Bad input. Try again: ");
        scanf("%*[^\n]");
        code = scanf("%d%c", out, &t);
    }
    return SUCCESS;
}

int input_hd(short *out) {
    char t;
    int code = scanf("%hd%c", out, &t);
    while (code != 2 || t != '\n') {
        if (code == EOF) {
            return EOF;
        }
        printf("Bad input. Try again: ");
        scanf("%*[^\n]");
        code = scanf("%hd%c", out, &t);
    }
    return SUCCESS;
}

int traverse(Graph *g) {
    if (g->len == 0) {
        printf("There are 0 vertices :c\n");
        return SUCCESS;
    }
    char *name = readline("Pick a name to start from: ");
    if (name == NULL) {
        return EOF;
    }
    Vertex *v = find(g, name);
    if (v == NULL) {
        return NOT_FOUND;
    }

    printf("DFS depth: ");
    int depth;
    do {
        int code = input_d(&depth);
        if (code == EOF) {
            free(name);
            return EOF;
        }
    } while (depth < 0);
    VerticesList *out = malloc(sizeof(VerticesList));
    out->next = NULL;
    int *colors = malloc(sizeof(int) * g->len);
    for (int i = 0; i < g->len; i++) {
        colors[i] = WHITE;
    }
    out->cur = v;
    colors[get_index(g, v)] = BLACK;
    dfs(g, out, colors, 0, depth);
    free(name);
    free(colors);

    VerticesList *cur = out;
    while (cur != NULL) {
        printf(" %s ", cur->cur->name);
        cur = cur->next;
    }
    printf("\n");
    free_list(out);

    return SUCCESS;
}

int shortest_opt(Graph *g) {
    char *name = readline("Input first person: ");
    if (name == NULL) {
        return EOF;
    }
    char *target = readline("Input second person: ");
    if (target == NULL) {
        free(name);
        return EOF;
    }
    int index = get_index(g, find(g, target));
    if (index == NOT_FOUND) {
        return NOT_FOUND;
    }

    int *shortest_indices = shortest_path(g, name);
    if (shortest_indices == NULL) {
        return NOT_FOUND;
    }
    if (shortest_indices[index] == -1) {
        printf("You can't get from %s to %s, at least with >0 attitude\n", name, target);
    } else {
        int cur = shortest_indices[index];
        printf("· %s\n", g->vertices[index].name);
        while (strcmp(g->vertices[cur].name, name) != 0) {
            printf("↑ %s\n", g->vertices[cur].name);
            cur = shortest_indices[cur];
        }
        printf("· %s\n", name);
        
    }
    // for (int i = 0; i < g->len; i++) {
    //     printf("%d\n", shortest_indices[i]); // DEBUG
    // }
    free(shortest_indices);
    free(name);
    free(target);
    return SUCCESS;
}

int special_opt(Graph *g) {
    scc(g);
    return SUCCESS;
}

int add_vertex_opt(Graph *g) {
    char *name = readline("Input new name: ");
    if (name == NULL) {
        return EOF;
    }
    int code = add_vertex(g, name);
    free(name);
    return code;
}

int add_edge_opt(Graph *g) {
    char *from = readline("Name of \"from\" vertex: ");
    if (from == NULL) {
        return EOF;
    }
    char *to = readline("Name of \"to\" vertex: ");
    if (to == NULL) {
        free(from);
        return EOF;
    }
    short attitude;
    printf("Attitude(from -10 to 10): ");
    int out = input_hd(&attitude);
    if (out == EOF) {
        return EOF;
    }
    while (attitude > 10 || attitude < -10)
    {
        printf("Bad number, try again: ");
        out = input_hd(&attitude);
        if (out == EOF) {
            return EOF;
        }
    }
    int code = add_edge(g, from, to, attitude);
    free(from);
    free(to);
    return code;
}

int delete_vertex_opt(Graph *g) {
    char *name = readline("Input name of needed vertex: ");
    if (name == NULL) {
        return EOF;
    }
    int code = delete_vertex(g, name);
    free(name);
    return code;
}

int delete_edge_opt(Graph *g) {
    char *from = readline("Name of \"from\" vertex: ");
    if (from == NULL) {
        return EOF;
    }
    char *to = readline("Name of \"to\" vertex: ");
    if (to == NULL) {
        free(from);
        return EOF;
    }
    int code = delete_edge_by_names(g, from, to);
    free(from);
    free(to);
    return code;
}

int rename_vertex_opt(Graph *g) {
    char *cur = readline("Input current name: ");
    if (cur == NULL) {
        return EOF;
    }
    char *new = readline("Input new name: ");
    if (new == NULL) {
        free(cur);
        return EOF;
    }

    int code = change_vertex(g, cur, new);
    free(cur);
    free(new);
    return code;
}

int change_edge_opt(Graph *g) {
    char *from = readline("Name of \"from\" vertex: ");
    if (from == NULL) {
        return EOF;
    }
    char *to = readline("Name of \"to\" vertex: ");
    if (to == NULL) {
        free(from);
        return EOF;
    }
    short attitude;
    printf("New attitude(from -10 to 10): ");
    int out = input_hd(&attitude);
    if (out == EOF) {
        return EOF;
    }
    while (attitude > 10 || attitude < -10)
    {
        printf("Bad number, try again: ");
        out = input_hd(&attitude);
        if (out == EOF) {
            return EOF;
        }
    }
    int code = change_edge(g, from, to, attitude);
    free(from);
    free(to);
    return code;
}