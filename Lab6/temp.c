#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

typedef struct queue {
    node_t *front;
    node_t *rear;
} queue_t;

void enqueue(queue_t *q, int value) {
    node_t *node = (node_t *) malloc(sizeof (node_t));
    node->value = value;
    node->next = q->rear;

    q->rear = node;
    
    if (q->front == NULL) 
        q->front = node;
}

int dequeue(queue_t *q) {
    if (q->front == NULL)
        return -1;

    node_t *tmp = q->front;
    int value = q->front->value;

    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->rear;
        while (q->front->next != tmp)
            q->front = q->front->next;
        q->front->next = NULL;
    }
    free(tmp);
    return value;
}