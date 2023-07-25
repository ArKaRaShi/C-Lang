#include <stdio.h>
#include <stdlib.h>

int **make2DArray(int size) {
    int **ptr = (int **) malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) 
        *(ptr + i) = (int *) malloc(sizeof(int) * size);
    return ptr;
}

void initializeZero(int **ptr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) 
            *(*(ptr + i) + j) = 0;
    }
}

void displayArray(int **ptr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) 
            printf("%d ", *(*(ptr + i) + j));
        printf("\n");
    }
}

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
    int firstPart = 1;
    int currRow = size - 1, currCol = 0, totalBox = size * size;
    for (int i = 0; i < totalBox; i++) {

        if (firstPart) {
            if (currDirection % 2 == 0) {
                *(*(ptr + currRow) + currCol) =  number;
                currRow--;
                currCol--;

                if (currRow < 0) {
                    firstPart = 0;
                    currDirection++;
                    currRow = 0;
                    currCol = 1;
                }
                else if (currCol < 0) {
                    currDirection++;
                    currCol = 0;

                }
            }
            else {
                *(*(ptr + currRow) + currCol) =  number;
                currCol++;
                currRow++;

                if (currCol == size) {
                    firstPart = 0;
                    currDirection++;
                    currRow = size - 2;
                    currCol = size - 1;
                }
                else if (currRow == size) {
                    currDirection++;
                    currRow = size - 1;
                }
            }
        }

        else {
            if (currDirection % 2 == 0) {
                *(*(ptr + currRow) + currCol) =  number;
                currRow--;
                currCol--;

                if (currRow < 0) {
                    currDirection++;
                    currRow = 0;
                    currCol += 2;
                }
            }
            else {
                *(*(ptr + currRow) + currCol) =  number;
                currRow++;
                currCol++;
                
                if (currCol == size) {
                    currDirection++;
                    currCol = size - 1;
                    currRow -= 2;
                }
            }
        }

        number++;
    }
}

int isZero(int **ptr, int row, int col) {
    if (*(*(ptr + row) + col) == 0) return 1; 
    return 0;
}

void pattern4(int **ptr, int size) {
    int increment[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int rowIncrement, colIncrement, currRow = 0, currCol = 0;
    int totalChangeDirection = 0, currDirection = 0, changeDirection = 0;
    int number = 1, totalBox = size * size;


    initializeZero(ptr, size);
    rowIncrement = increment[0][0];
    colIncrement = increment[0][1];
    for (int i = 0; i < totalBox; i++) {
        if (currDirection == 0 && currRow == size) changeDirection = 1;
        if (currDirection == 1 && currCol == size) changeDirection = 1;
        if (currDirection == 2 && currRow < 0) changeDirection = 1;
        if (currDirection == 3 && currCol < 0) changeDirection = 1;
      
        if (changeDirection) {
            currRow -= rowIncrement;
            currCol -= colIncrement;
            totalChangeDirection++;
            i--;

            currDirection = totalChangeDirection % 4;
            rowIncrement = increment[currDirection][0];
            colIncrement = increment[currDirection][1];

            currRow += rowIncrement;
            currCol += colIncrement;
            changeDirection = 0;
        }
        else {
            if (isZero(ptr, currRow, currCol)) {
                *(*(ptr + currRow) + currCol) = number;
                currRow += rowIncrement;
                currCol += colIncrement;
                number++;
            }
            else {
                changeDirection = 1;
                i--;
            }
        }
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



