#include <stdio.h>
#include <stdlib.h>

//test
//another test

typedef struct node {
    int order;
    int value;
} node_t;

typedef struct graph {
    node_t *graph_arr;
    int **graph_lines;
    int size;
} graph_t;

typedef struct stack {
    node_t *data;
    struct stack *next;
} stack_t;

stack_t *push(stack_t *s, node_t *node_data) {
    stack_t *temp_stack = (stack_t *) malloc(sizeof(stack_t));
    temp_stack->data = node_data;
    temp_stack->next = s;
    s = temp_stack;
    return s;
}

void pop(stack_t **s) {
    stack_t *temp_stack = *s;
    *s = (*s)->next;
    free(temp_stack);
}

node_t *top(stack_t *s) {
    return s->data;
}

int empty(stack_t *s) {
    if (s == NULL)
        return 1;
    return 0;
}

graph_t *create_graph(int size) {
    graph_t *new_graph = (graph_t *) malloc(sizeof(graph_t));
    new_graph->graph_arr = (node_t *) malloc(sizeof(node_t) * size);
    new_graph->graph_lines = (int **) malloc(sizeof(int *) * size);
    new_graph->size = size;
    for (int row = 0; row < size; row++) 
        new_graph->graph_lines[row] = (int *) malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        (new_graph->graph_arr + i)->order = i;
        (new_graph->graph_arr + i)->value = -1;
    }
    return new_graph;
}

void reset_graph_node_value(graph_t *uw_graph) {
    for (int node = 0; node < uw_graph->size; node++)
        uw_graph->graph_arr[node].value = -1;
}

void setup_graph_line_weight(graph_t *uw_graph) {
    for (int i = 0; i < uw_graph->size; i++)
        for (int j = 0; j < uw_graph->size; j++)
            uw_graph->graph_lines[i][j] = 0;
}

int shortest_path(graph_t *uw_graph, int start_node, int destination_node) {
    if (start_node == destination_node)
        return 0;

    stack_t *s = NULL;
    node_t *curr_node;
    int lines = uw_graph->size;
    int curr_value, des_value, line_weight;

    s = push(s, (uw_graph->graph_arr + start_node));
    while(!empty(s)) {
        curr_node = top(s);
        pop(&s);
        for (int line = 0; line < lines; line++) {
            curr_value = uw_graph->graph_arr[curr_node->order].value;
            des_value = uw_graph->graph_arr[line].value;
            line_weight = uw_graph->graph_lines[curr_node->order][line];
            if (line_weight > 0) {
                if (des_value == -1 || (curr_value + line_weight < des_value)) {
                    uw_graph->graph_arr[line].value = curr_value + line_weight;
                    s = push(s, (uw_graph->graph_arr + line));
                }
            }
        }
    }

    if (uw_graph->graph_arr[destination_node].value == -1)
        return -1;
    return uw_graph->graph_arr[destination_node].value + 1;
}

void destroy_graph(graph_t *uw_graph) {
    free(uw_graph->graph_arr);
    for (int i = 0; i < uw_graph->size; i++)
        free((*(uw_graph->graph_lines + i)));
    free(uw_graph->graph_lines);
    free(uw_graph);
}

int main() {
    int total_nodes, total_lines, total_questions;
    scanf("%d %d %d", &total_nodes, &total_lines, &total_questions);
    int start_node, destination_node, weight, result;

    graph_t *uw_graph = create_graph(total_nodes);
    setup_graph_line_weight(uw_graph);

    for (int i = 0; i < total_lines; i++) {
        scanf("%d %d %d", &start_node, &destination_node, &weight);
        uw_graph->graph_lines[start_node][destination_node] = weight;
        uw_graph->graph_lines[destination_node][start_node] = weight;
    }

    for (int i = 0; i < total_questions; i++) {
        scanf("%d %d", &start_node, &destination_node);
        reset_graph_node_value(uw_graph);
        result = shortest_path(uw_graph, start_node, destination_node);
        printf("%d\n", result);
    }
    destroy_graph(uw_graph);
    return 0;
}