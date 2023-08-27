#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;
typedef node_t stack_t;

stack_t *push(stack_t *s, int value) {
    stack_t *tempNode = (stack_t *) malloc(sizeof(stack_t));
    tempNode->data = value;
    tempNode->next = s;
    s = tempNode;
    return s;
}

void top(stack_t *s) {
    if (s == NULL)
        printf("Stack is empty.\n");
    else
        printf("%d\n", s->data);
}

void empty(stack_t *s) {
    if (s == NULL)
        printf("Stack is empty.\n");
    else
        printf("Stack is not empty.\n");
}

stack_t *pop(stack_t *s) {
    if (s != NULL) {
        stack_t *tempNode = s;
        s = s->next;
        free(tempNode);
    }
    return s;
}

void size(stack_t *s) {
    int stackSize = 0;
    while (s != NULL) {
        s = s->next; 
        stackSize++;
    }
    printf("%d\n", stackSize);
}

int main(void) {
    stack_t *s = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d", &value);
                s = push(s, value);
                break;
            case 2:
                top(s);
                break;
            case 3:
                s = pop(s);
                break;
            case 4:
                empty(s);
                break;
            case 5:
                size(s);
                break;
        }
    }   
    return 0;
}