#include <stdio.h>
#define ARRSIZE 17

void findUseIndex(int value, int currIndex, int powOfTwo[], int modifyArr[]) {
    while (value > 0) {
        if (powOfTwo[currIndex] <= value) {
            value -= powOfTwo[currIndex];
            modifyArr[currIndex] = 1;
        }
        currIndex--;
    }
}

void displayArr(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

int main() {
    int powOfTwoArr[ARRSIZE] = {1, 2, 4, 8, 16, 
                                32, 64, 128, 256, 512, 
                                1024, 2048, 4096, 8192, 16384,
                                32768, 65536};
    int useIndexWidth[ARRSIZE] = {0}, useIndexHeight[ARRSIZE] = {0};
    int pointIndex = ARRSIZE - 1;

    int width, height, result = 0;
    scanf("%d %d", &width, &height);
    findUseIndex(width, pointIndex, powOfTwoArr, useIndexWidth);
    findUseIndex(height, pointIndex, powOfTwoArr, useIndexHeight);
    for (int i = 0; i < ARRSIZE; i++) {
        for (int j = 0; j < ARRSIZE; j++) {
            if (useIndexWidth[i] && useIndexHeight[j]) {
                result += (powOfTwoArr[i] > powOfTwoArr[j]) ? powOfTwoArr[i] / powOfTwoArr[j] : powOfTwoArr[j] / powOfTwoArr[i];
            }
        }
    }
    printf("%d", result);
    return 0;
}

// O(1)