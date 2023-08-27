#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    float number;
    struct node *next;
} node_t;
typedef node_t stack_t;

int isOperator(char c) {
    if (c == '+' || 
        c == '-' || 
        c == '*' || 
        c == '/')
        return 1;
    return 0;
}

float calculate(float num1, float num2, char operator) {
    float result;
    switch (operator) {
        case '+':
            result = num2 + num1;
            break;
        case '-':
            result = num2 - num1;
            break;
        case '*':
            result = num2 * num1;
            break;
        case '/':
            result = num2 / num1;
            break;
        default:
            break;
    }
    return result;
}

void push(stack_t **s, float number) {
    stack_t *newNode = (stack_t *) malloc(sizeof(stack_t));
    newNode->number = number;
    newNode->next = *s;
    *s = newNode;
}

float pop(stack_t **s) {
    stack_t *tempNode = *s;
    float value = tempNode->number;
    *s = (*s)->next;
    free(tempNode);
    return value;
}

int main() {
    int n;
    scanf("%d\n", &n);
    char inputChar[n + 1];
    scanf("%s", inputChar);
    stack_t *s = NULL;
    char tempC;
    float number1, number2, result;
    for (int i = 0; i < n; i++) {
        tempC = inputChar[i];

        if (isOperator(tempC)) {
            number1 = pop(&s);
            number2 = pop(&s);
            result = calculate(number1, number2, tempC);
            push(&s, result);
        } else 
            push(&s, (float)(tempC - 48));
    }
    free(s);
    printf("%.2f", result);
    return 0;
}