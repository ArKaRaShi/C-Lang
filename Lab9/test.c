#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

node_t *create(int value) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

int main() {
    node_t *first = create(1);
    node_t *second = create(2);
    first->next = second;

    if (first->next != NULL)
        printf("%d\n", first->next->value);

    free(second);
    second = NULL;

    if (first->next == NULL)
        printf("NULL.");
    else
        printf("%d", first->next->value);

    return 0;
}