#include <stdio.h>
#include <stdlib.h>

char **makeTable(int size) {
    char **ptr;
    ptr = (char **) malloc(sizeof (char *) * size);
    for (int i = 0; i < size; i++) 
        *(ptr + i) = (char *) malloc(sizeof (char) * size); 
    return ptr;
}

void freeTable(char **ptr, int size) {
    for (int i = 0; i < size; i++) 
        free(*(ptr + i));
    
    free(ptr);
}

void displayTable(char **ptr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}

void getInput(char **ptr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%c", &*(*(ptr + i) + j));
        }
        while (getchar() != '\n') {}
    }
}

void *findStartPostion(char **map, int size) {
    
    int *startPositionPtr = (int *) malloc(sizeof (int) * 2);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(*(map + i) + j) == 'S') {
                *startPositionPtr = i;
                *(startPositionPtr + 1) = j;
            }
        }
    }
    return startPositionPtr;
}

int checkCondition(int desRow, int desCol, int prevDirection, int invalidDirection, int size) {
    if (desRow >= 0 && desCol >= 0 && desRow < size && desCol < size) 
        if (prevDirection != invalidDirection) 
            return 1;
    return 0;
}

int dfsRecursive(char **map, int size, int currRow, int currCol, int prevDirection) {
    int desRow, desCol, goalReach;
    int nextDirection[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int invalidDirection[4] = {2, 3, 0, 1};
    char desSymbol, currSymbol = *(*(map + currRow) + currCol); 
    if (currSymbol == 'G') return 1;

    for (int i = 0; i < 4; i++) {
        desRow = nextDirection[i][0] + currRow;
        desCol = nextDirection[i][1] + currCol;
        if (checkCondition(desRow, desCol, prevDirection, i, size)) {
            desSymbol = *(*(map + desRow) + desCol);
            if (desSymbol != '#') {
                goalReach = dfsRecursive(map, size, desRow, desCol, invalidDirection[i]);
                if (goalReach) {
                    if (currSymbol != 'S') *(*(map + currRow) + currCol) = '.';
                    return 1;
                }
            }
        }
    }
    return 0;
}


int main() {
    char **pTable;
    int *sPosPtr;
    int tableSize;

    scanf("%d\n", &tableSize);

    pTable = makeTable(tableSize);
    getInput(pTable, tableSize);

    sPosPtr = findStartPostion(pTable, tableSize);
    dfsRecursive(pTable, tableSize, *sPosPtr, *(sPosPtr + 1), -1);
    displayTable(pTable, tableSize);
    freeTable(pTable, tableSize);
    return 0;
}

/*
12
############
#   #      # 
S # # #### #
### #    # #
#    ### # G
#### # # # #
#  # # # # #
## # # # # #
#        # #
###### ### #
#      #   #
############
*/