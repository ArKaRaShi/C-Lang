#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDLENGTH 16

typedef struct node {
    int priority;
    char *word;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;

typedef struct heap {
    tree_t **t_data;
    int last_index;
} heap_t;

node_t *create_tree_node() {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->word = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

heap_t *init_heap(int size) {
    heap_t *new_heap = (heap_t *) malloc(sizeof(heap_t));
    new_heap->t_data = (tree_t **) malloc(sizeof(tree_t *) * size);
    for (int itr = 0; itr < size; itr++)
        *(new_heap->t_data + itr) = create_tree_node();
    new_heap->last_index = -1;
    return new_heap;
}

char *init_word(char in_word[]) {
    if (in_word == NULL)
        return NULL;
    
    int word_length = strlen(in_word);
    char *word = (char *) malloc(sizeof(char) * word_length + 1);
    strcpy(word, in_word);
    return word;
}

int find_parent_index(int index) {
    if (index % 2 == 0)
        return (index - 1) / 2;
    return index / 2;
}

int find_child_index(int index) {
    return index * 2 + 1;
}

int out_of_range(int curr_index, int start_index, int end_index) {
    if (curr_index >= start_index && curr_index <= end_index)
        return 0;
    return 1;
}

int minimum(int data1, int data2) {
    if (data1 > data2)
        return data2;
    return data1;
}

/* return 1 if data1 is more than data2 */
int compare_min(int data1, int data2) {
    if (data2 < data1)
        return 1;
    return 0;
}

void swap_data(heap_t *min_heap, int index1, int index2) {
    tree_t *temp_t_data = min_heap->t_data[index1];
    min_heap->t_data[index1] = min_heap->t_data[index2];
    min_heap->t_data[index2] = temp_t_data;
}

void percolate_up(heap_t *min_heap, int start_index) {
    const int first_index = 0;
    const int last_index = min_heap->last_index;

    int curr_index = start_index;
    int parent_index = find_parent_index(curr_index);
    tree_t *curr_t_data, *parent_t_data;

    while ((!out_of_range(parent_index, first_index, last_index)) && (curr_index != parent_index)) {
        curr_t_data = *(min_heap->t_data + curr_index);
        parent_t_data = *(min_heap->t_data + parent_index);

        if (compare_min(parent_t_data->priority, curr_t_data->priority))
            swap_data(min_heap, curr_index, parent_index);
        else break; 

        curr_index = parent_index;
        parent_index = find_parent_index(curr_index);
    }
}

void percolate_down(heap_t *min_heap, int start_index) {
    const int first_index = 0;
    const int last_index = min_heap->last_index;

    int curr_index = start_index;
    tree_t *curr_t_data, *child_t_data1, *child_t_data2;
    int child_index1 = find_child_index(curr_index);
    int child_index2 = find_child_index(curr_index) + 1;

    while (!out_of_range(child_index1, first_index, last_index)) {
        curr_t_data = *(min_heap->t_data + curr_index);
        child_t_data1 = *(min_heap->t_data + child_index1);
        child_t_data2 = *(min_heap->t_data + child_index2);

        if (compare_min(curr_t_data->priority, child_t_data1->priority) ||
        compare_min(curr_t_data->priority, child_t_data2->priority)) {
            if (child_t_data1->priority == minimum(child_t_data1->priority, child_t_data2->priority)) {
                swap_data(min_heap, curr_index, child_index1);
                curr_index = child_index1;
            } else {
                swap_data(min_heap, curr_index, child_index2);
                curr_index = child_index2;
            }
        } else
            break;

        child_index1 = find_child_index(curr_index);
        child_index2 = find_child_index(curr_index) + 1;
    }
}

void insert_with_tree(heap_t *min_heap, tree_t *t_data) {
    int last_index = min_heap->last_index + 1;
    *(min_heap->t_data + last_index) = t_data;
    min_heap->last_index = last_index;
    percolate_up(min_heap, last_index);
}

void insert(heap_t *min_heap, char word[], int priority) {
    int last_index = min_heap->last_index + 1;
    (*(min_heap->t_data + last_index))->word = init_word(word);
    (*(min_heap->t_data + last_index))->priority = priority;
    min_heap->last_index = last_index;
    percolate_up(min_heap, last_index);
}

tree_t *delete_min(heap_t *min_heap) {
    int last_index = min_heap->last_index;
    tree_t *substitude_data = *(min_heap->t_data + last_index);
    tree_t *delete_tree = *(min_heap->t_data);
    *(min_heap->t_data) = substitude_data;
    min_heap->last_index = last_index - 1;
    percolate_down(min_heap, 0);
    return delete_tree;
}

tree_t *combine_tree(tree_t *t_data1, tree_t *t_data2) {
    tree_t *new_tree = create_tree_node();
    new_tree->left = t_data1;
    new_tree->right = t_data2;
    new_tree->priority = t_data1->priority + t_data2->priority;
    return new_tree;
}

void huffman_encoding(heap_t *min_heap) {
    tree_t *t_data1 = NULL, *t_data2 = NULL, *new_tree = NULL;
    while (min_heap->last_index > 0) {
        t_data1 = delete_min(min_heap);
        t_data2 = delete_min(min_heap);
        new_tree = combine_tree(t_data1, t_data2);
        insert_with_tree(min_heap, new_tree);
    }
}

void print_code(tree_t *t, int arr[], int last_index) {
    if (t->word == NULL) {
        arr[last_index] = 0;
        print_code(t->left, arr, last_index + 1);
        arr[last_index] = 1;
        print_code(t->right, arr, last_index + 1);
    } else {
        printf("%s: ", t->word);
        for (int i = 0; i < last_index; i++) 
            printf("%d", arr[i]);
        printf("\n");
    }   
}

void destroy_tree(tree_t *t) {
    if (t != NULL) {
        destroy_tree(t->left);
        destroy_tree(t->right);
        free(t);
    }
}

void destroy_heap(heap_t *min_heap) {
    tree_t *t = *(min_heap->t_data);
    destroy_tree(t);
    free(min_heap->t_data);
}

int main(void) {
    heap_t *min_heap = NULL;
    int n, priority;
    char temp_word[15];
    scanf("%d", &n);
    min_heap = init_heap(n);


    while (getchar() != '\n') {}
    for (int i = 0; i < n; i++) {
        scanf("%s %d", temp_word, &priority);
        insert(min_heap, temp_word, priority);
    }
    int arr[n];
    huffman_encoding(min_heap);
    print_code(*(min_heap->t_data), arr, 0);
    return 0;
}