#include <stdio.h>

void swap(int *arr, int pos1, int pos2) {
    int temp_data = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp_data;
}

void print_array(int *arr, int size) {
    for (int index = 0; index < size; index++)
        printf("%d ", arr[index]);
    printf("\n");
}

void insertion_sort(int *arr, int size) {
    for (int index = 1; index < size; index++) {
        int curr_pos = index;
        while (curr_pos > 0) {
            if (arr[curr_pos] > arr[curr_pos - 1])
                break;
            swap(arr, curr_pos, curr_pos - 1);
            curr_pos--;
        }
        print_array(arr, size); 
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) 
        scanf("%d", &arr[i]);
    insertion_sort(arr, n);
    return 0;
}