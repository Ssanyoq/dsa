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

#define LIMIT 100000

/*
tests:
2 a/1/20 b/1/15 c/2/10 d/5/8 e/6/5 f/6/9
2 a/1/20 b/1/15 c/2/10 d/5/8 e/6/5 f/6/9 g/7/8 h/8/9 i/8/1 j/10/123 k/22/5
*/


int main() {
    int stands;
    Queue *q = init(LIMIT);
    char *inp = readline("Input:\n");
    short is_first = 1;
    char **slashed = (char **)malloc(LIMIT * LIMIT * sizeof(char *));
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
    int exit_i;
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
    int i;
    for (i = 0; i < stands; i++) {
        queues[i] = init(LIMIT);
    }
    int time_limit = check(q)->ta;
    int *pop_time = (int *)malloc(stands * sizeof(int));
    for (int i = 0; i < stands; i++) {
        pop_time[i] = -1;
    }
    int last_taken = -1;
    for (int i = 0;;) {
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


        //finding next event
        int min_time = 9999999;
        int min_queue = -2; // -1 - needs to find new one, [0, stands) - needs to get new customer, -2 - undefined, terminate loop
        for (int j = 0; j < stands; j++) {
            if (pop_time[j] != -1) {
                if (min_time > pop_time[j]) {
                    min_time = pop_time[j];
                    min_queue = j;
                }
            }
        }
        Item *tmp = check(q);
        if (tmp != NULL) {
            if (tmp->ta < min_time) {
                min_time = tmp->ta;
                min_queue = -1;
            }
        }
        //now processing
        if (min_queue == -2) {
            break;
        } else if (min_queue == -1) {
            pop(q, tmp);
            last_taken = (last_taken + 1) % stands;
            push(queues[last_taken], tmp);
            if (pop_time[last_taken] == -1) {
                pop_time[last_taken] = tmp->ta + tmp->ts;
            }
            
        } else { // pops from queue
            Item *_;
            int out = pop(queues[min_queue], _);
            if (out == ERR_CODE) {
                for (int k = 0; k < stands; k++) {
                    if (pop_time[k] > i) {
                        i = pop_time[k];
                        pop(queues[k], _);
                    }
                }
                exit_i = i;
                break;
            }
            if (check(queues[min_queue]) != NULL) {
                pop_time[min_queue] = min_time + check(queues[min_queue])->ts;
            }

        }
        i = min_time;
    }
    printf("%d\n", exit_i);
        for (int j = 0; j < stands; j++) {
            printf("№%d ", j + 1);
            print_queue(queues[j]);
        }
        printf("\n");
    return 0;
}