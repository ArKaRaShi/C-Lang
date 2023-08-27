#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *next;
} node_t;
typedef node_t queue_t;

queue_t *enqueue(queue_t *q, int value) {
    queue_t *tempNode = (queue_t *) malloc(sizeof(queue_t));
    queue_t *currNode;

    tempNode->data = value;
    tempNode->next = NULL;

    if (q == NULL)
        q = tempNode;

    else {
        currNode = q;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next = tempNode;
    }
    return q;
}

queue_t *dequeue(queue_t *q) {
    if (q != NULL) {
        queue_t *tempNode = q;
        q = q->next;
        printf("%d\n", tempNode->data);
        free(tempNode);
    } else
        printf("Queue is empty.\n");
    return q;
}

void show(queue_t *q) {
    if (q == NULL)
        printf("Queue is empty.\n");
    else {
        while (q != NULL) {
            printf("%d ", q->data);
            q = q->next;
        }
        printf("\n");
    }
}

void empty(queue_t *q) {
    if (q == NULL)
        printf("Queue is empty.\n");
    else
        printf("Queue is not empty.\n");
}

void size(queue_t *q) {
    int queueSize = 0;
    while (q != NULL) {
        queueSize++;
        q = q->next;
    }
    printf("%d\n", queueSize);
}

int main(void) {
    queue_t *q = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d", &value);
                q = enqueue(q, value);
                break;
            case 2:
                q = dequeue(q);
                break;
            case 3:
                show(q);
                break;
            case 4:
                empty(q);
                break;
            case 5:
                size(q);
                break;
        }
    }
    return 0;
}