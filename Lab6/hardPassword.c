#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char c;
    struct node *next;
} node_t;
typedef node_t stack_t;

int empty(stack_t *s) {
    if (s == NULL)
        return 1;
    return 0;
}

void push(stack_t **s, char c) {
    stack_t *newNode = (stack_t *) malloc(sizeof(stack_t));
    newNode->c = c;
    newNode->next = *s;
    *s = newNode;
}

char top(stack_t *s) {
    if (!empty(s))
        return s->c;
    return 0;
}

void pop(stack_t **s) {
    stack_t *tempNode = *s;
    *s = (*s)->next;
    free(tempNode);
}

int main() {
    stack_t *s = NULL;
    char tempC;
    
    while ((tempC = getchar()) != 'x') {
        push(&s, tempC);
    }

    int condition = 1;
    while ((tempC = getchar()) != 'y') {
        if (top(s) == tempC)
            pop(&s);
        else
            condition = 0;
    }
    if (!empty(s))
        condition = 0;
    printf("%d", condition);
    return 0;
}