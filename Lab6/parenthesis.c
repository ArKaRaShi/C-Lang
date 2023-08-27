#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char character;
    struct node *next;
} node_t;

typedef node_t stack_t;

stack_t *push(stack_t *s, char c) {
    stack_t *tempNode = (stack_t *) malloc(sizeof(stack_t));
    tempNode->character = c;
    tempNode->next = s;
    s = tempNode;
    return s;
}

int empty(stack_t *s) {
    if (s == NULL)
        return 1;
    return 0;
}

char top(stack_t *s) {
    return s->character;
}   

stack_t *pop(stack_t *s) {
    if (s != NULL) {
        stack_t *tempNode = s;
        s = s->next;
        free(tempNode);
    }
    return s;
}

int openSide(char c) {
    if (c == '[' || c == '{' || c == '(')
        return 1;
    return 0;
}

int matching(char fisrtC, char secondC) {
    if (fisrtC == '(' && secondC == ')') return 1;
    if (fisrtC == '[' && secondC == ']') return 1;
    if (fisrtC == '{' && secondC == '}') return 1;
    return 0;
}

int main() {
    stack_t *s = NULL;
    int n, condition = 1;
    char inC;

    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        scanf("%c", &inC);
        if (openSide(inC))
            s = push(s, inC);
        else {
            if (empty(s)) {
                condition = 0;
                break;
            } else if (matching(top(s), inC)) { 
                s = pop(s);
            } else {
                s = push(s, inC);
            }
        }
    }
    if (!empty(s)) condition = 0;
    printf("%d", condition);
    return 0;
}