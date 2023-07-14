#include <stdio.h>
#include <stdlib.h>

void pattern1(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) 
            printf("%d ", (i + 1) + j * size);
        printf("\n");
    }
}

void pattern2(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j % 2 == 0) 
                printf("%d ", (i + 1) + j * size);
            else 
                printf("%d ", (size * 2 - i) + (j - 1) * size);
        }
        printf("\n");
    }
}

void pattern3(int **ptr, int size) {
    int currDirection = 0, number = 1;
    int currRow = size - 1, currCol = 0, totalBox = size * size;
    for (int i = 0; i < totalBox; i++) {
        
        if (currDirection % 2 == 0) {
            *(*(ptr + currRow) + currCol) =  number;
            currRow--;
            currCol--;
        }
        else {



        }

        if (currRow < 0 || currCol < 0)

    } 



    freeMemory(pTable);
}

void pattern4(int size) {
    


    freeMemory(pTable);
}

int **make2DArray(int size) {
    int **ptr = (int **) malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) 
        *(ptr + i) = (int *) malloc(sizeof(int) * size);
    return ptr;
}

void displayArray(int **ptr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) 
            printf("%d ", *(*(ptr + i) + j));
        printf("\n");
    }
}

void freeMemory(int **ptr, int size) {
    for (int i = 0; i < size; i++) 
        free(*(ptr + i));
    free(ptr);
}

void processPattern(int size, int pattern) {
    if (pattern == 1 || pattern == 2) {
        if (pattern == 1) pattern1(size);
        if (pattern == 2) pattern2(size);
    }
    else {
        int **pTable = make2DArray(size);
        if (pattern == 3) pattern3(pTable, size);
        if (pattern == 4) pattern4(pTable, size);
        displayArray(pTable, size);
        freeMemory(pTable, size);
    }
}



int main() {
    int size, pattern;
    scanf("%d %d", &size ,&pattern);
    processPattern(size, pattern);
    return 0;
}



