#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int order;
    int visited;
} node_t;

typedef struct graph {
    node_t *graph_arr;
    int **graph_lines;
    int **graph_reachable;
    int size;
} graph_t;

typedef struct stack {
    node_t *vertex;
    struct stack *next;
} stack_t;

stack_t *push(stack_t *s, node_t *vertex) {
    stack_t *temp_stack = (stack_t *) malloc(sizeof(stack_t));
    temp_stack->vertex = vertex;
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
    return s->vertex;
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
    new_graph->graph_reachable = (int **) malloc(sizeof(int *) * size);
    new_graph->size = size;
    for (int row = 0; row < size; row++) {
        new_graph->graph_lines[row] = (int *) malloc(sizeof(int) * size);
        new_graph->graph_reachable[row] = (int *) malloc(sizeof(int) * size);
    }

    for (int i = 0; i < size; i++) {
        (new_graph->graph_arr + i)->order = i;
        (new_graph->graph_arr + i)->visited = 0;
    }
    
    return new_graph;
}

void setup_graph_table(int **table, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            table[i][j] = 0;
}   

void reset_graph_visited(graph_t *d_graph) {
    for (int i = 0; i < d_graph->size; i++)
        d_graph->graph_arr[i].visited = 0;
}

void reset_arr_to_zero(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

void copy_arr(int *arr1, int *arr2, int size) {
    for (int i = 0; i < size; i++)
        arr1[i] = arr2[i];
}

void find_reachable_vertex(graph_t *d_graph, int start_vertex, int *reachable_vertex) {
    stack_t *s = NULL;
    s = push(s, (d_graph->graph_arr + start_vertex));

    int graph_size = d_graph->size;
    int reachable;
    node_t *curr_vertex, *des_vertex;
    while (!empty(s)) {
        curr_vertex = top(s);
        pop(&s);
        
        reachable_vertex[curr_vertex->order] = 1;
        curr_vertex->visited = 1;

        for (int i = 0; i < graph_size; i++) {
            reachable = d_graph->graph_lines[curr_vertex->order][i];
            des_vertex = (d_graph->graph_arr + i);
            if (reachable && !des_vertex->visited) {
                s = push(s, (d_graph->graph_arr + i));
            }
        }
    }
}

void scc(graph_t *d_graph, int *result) {
    int graph_size = d_graph->size;
    int *reachable_vertex = (int *) malloc(sizeof(int) * graph_size);
    int *temp_result = (int *) malloc(sizeof(int) * graph_size);
    int max_scc_size = 0, temp_scc_size;
    for (int curr_vertex = 0; curr_vertex < graph_size; curr_vertex++) {
        reset_arr_to_zero(reachable_vertex, graph_size);
        reset_graph_visited(d_graph);
        find_reachable_vertex(d_graph, curr_vertex, reachable_vertex);
        copy_arr(d_graph->graph_reachable[curr_vertex], reachable_vertex, graph_size);
    }

    int reachable1, reachable2;
    for (int curr_vertex = 0; curr_vertex < graph_size; curr_vertex++) {
        reset_arr_to_zero(temp_result, graph_size);
        temp_scc_size = 0;
        for (int des_vertex = 0; des_vertex < graph_size; des_vertex++) {
            reachable1 = d_graph->graph_reachable[curr_vertex][des_vertex];
            reachable2 = d_graph->graph_reachable[des_vertex][curr_vertex];
            if (reachable1 && reachable2) {
                temp_result[des_vertex] = 1;
                temp_scc_size++;
            }
        }
        if (temp_scc_size > max_scc_size) {
            copy_arr(result, temp_result, graph_size);
            max_scc_size = temp_scc_size;
        }
    }
}

int main() {
    int total_nodes, total_lines;
    scanf("%d %d", &total_nodes, &total_lines);
    int start_vertex, des_vertex;
    int *max_result_scc = (int *) malloc(sizeof(int) * total_nodes);
    reset_arr_to_zero(max_result_scc, total_nodes);

    graph_t *d_graph = create_graph(total_nodes);
    setup_graph_table(d_graph->graph_lines, d_graph->size);
    setup_graph_table(d_graph->graph_reachable, d_graph->size);

    for (int i = 0; i < total_lines; i++) {
        scanf("%d %d", &start_vertex, &des_vertex);
        d_graph->graph_lines[start_vertex][des_vertex] = 1;
    }

    scc(d_graph, max_result_scc);
    for (int i = 0; i < total_nodes; i++)
        if (max_result_scc[i])
            printf("%d ", i);

    return 0;
}