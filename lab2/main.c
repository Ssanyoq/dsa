#ifdef LIST
#include "list_queue.h"
#endif
#ifdef VECTOR
#include "vector_queue.h"
#endif

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#define LIMIT 10000


int main() {
    int stands;
    Queue *q = init(LIMIT);
    char *inp = readline("Input:\n");
    short is_first = 1;
    char **slashed = (char **)malloc(LIMIT * sizeof(char *));
    int arr_len = 0;
    while (inp != NULL)
    {
        char *word = strtok(inp, " \t");
        while (word != NULL) {
            if (is_first) {
                char *marker;
                stands = strtol(word, &marker, 10);
                if (marker == word) {
                    printf("Number not found, try again:\n");
                    goto WHILE_END;
                }
                is_first = 0;
            } else {
                slashed[arr_len] = (char *)malloc((strlen(word) + 1) * sizeof(char));
                memcpy(slashed[arr_len], word, (strlen(word) + 1) * sizeof(char));
                arr_len++;
            }
            word = strtok(NULL, " \t");
        }
        WHILE_END:
        free(inp);
        inp = readline("");
    }

    // now chars to Items
    for (int i = 0; i < arr_len; i++) {
        if (strchr(slashed[i], '/') == NULL) {
            goto END_OF_LOOP;
        }
        Item *new = (Item *)malloc(sizeof(Item));
        char *item_part = strtok(slashed[i], "/");
        new->id = (char *)malloc(sizeof(char) * (strlen(item_part) + 1));
        memcpy(new->id, item_part, (strlen(item_part) + 1) * sizeof(char));
        item_part = strtok(NULL, "/");
        char *marker;
        new->ta = strtol(item_part, &marker, 10);
        if (marker == item_part) {
            free(new);
            goto END_OF_LOOP;
        }
        item_part = strtok(NULL, "/");
        new->ts = strtol(item_part, &marker, 10);
        if (marker == item_part) {
            free(new);
            goto END_OF_LOOP;
        }
        push(q, new);
        END_OF_LOOP:
        free(slashed[i]);
    }
    print_queue(q);
    Queue **queues = (Queue **)malloc(sizeof(Queue *) * stands);
    for (int i = 0; i < stands; i++) {
        queues[i] = init(LIMIT);
    }
    int time_limit = check(q)->ta;
    int *pop_time = (int *)malloc(stands * sizeof(int));
    for (int i = 0; i <= time_limit;) {
        if (i == 0) {
            goto PRINTS;
        }

        PRINTS:
        printf("%d\n", i);
        for (int j = 0; j < stands; j++) {
            printf("№%d ", j + 1);
            print_queue(queues[j]);
        }
        printf("\n");
        break;
    }

    return 0;
}