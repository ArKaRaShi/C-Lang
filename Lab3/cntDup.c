#include <stdio.h>

#define SIZE 101

void initializeZero(int *arr, int n) {
    for (int i = 0; i < n; i++) 
        *(arr + i) = 0;
}

int main() {
    int n, temp, max = 0;
    scanf("%d", &n);
    int numbers[SIZE];
    initializeZero(numbers, SIZE);

    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        numbers[temp]++;
        if (numbers[temp] > max) max = numbers[temp];
    }

    for (int i = 0; i < SIZE; i++) {
        if (numbers[i] == max) printf("%d ", i);
    }
    
    return 0;
}