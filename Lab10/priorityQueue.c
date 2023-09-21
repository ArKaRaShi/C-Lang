#include <stdio.h>
#include <stdlib.h>
typedef struct heap {
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int size) {
    heap_t *new_heap = (heap_t *) malloc(sizeof(heap_t));
    new_heap->data = (int *) malloc(sizeof(int) * size);
    new_heap->last_index = -1;
    return new_heap;
}

int find_parent_index(int index) {
    if (index % 2 == 0)
        return (index - 1) / 2;
    return index / 2;
}

int out_of_range(int curr_index, int start_index, int end_index) {
    if (curr_index >= start_index && curr_index <= end_index)
        return 0;
    return 1;
}

/* return 1 if data2 is more than data 1 */
int compare_max(int data1, int data2) {
    if (data2 > data1)
        return 1;
    return 0;
}

void swap_data(heap_t *max_heap, int index1, int index2) {
    int temp_data = *(max_heap->data + index1);
    *(max_heap->data + index1) = *(max_heap->data + index2);
    *(max_heap->data + index2) = temp_data; 
}

void insert(heap_t *max_heap, int data) {
    int new_last_index = max_heap->last_index + 1;

    *(max_heap->data + new_last_index) = data;
    max_heap->last_index = new_last_index;

    int parent_index = find_parent_index(new_last_index);
    int curr_index = new_last_index;
    int curr_data, parent_data;
    while (!out_of_range(parent_index, 0, new_last_index)) {
        if (parent_index == curr_index)
            break;
        
        parent_data = *(max_heap->data + parent_index);
        curr_data = *(max_heap->data + curr_index);
        if (compare_max(parent_data, curr_data))
            swap_data(max_heap, parent_index, curr_index);
        else break;
        curr_index = parent_index;
        parent_index = find_parent_index(curr_index);
    }
}

void delete_max(heap_t *max_heap) {



}

void bfs(heap_t *max_heap) {
    for (int i = 0; i <= max_heap->last_index; i++) 
        printf("%d ", *(max_heap->data + i));
    printf("\n");
}

int main(void) {
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                insert(max_heap, data);
                break;
            // case 2:
            //     delete_max(max_heap);
            //     break;
            // case 3:
            //     printf("%d\n", find_max(max_heap));
            //     break;
            // case 4:
            //     scanf("%d %d", &old_key, &new_key);
            //     update_key(max_heap, old_key,
            //     new_key);
            //     break;
            case 5:
                bfs(max_heap);
                break;
        }
    }
    return 0;
}