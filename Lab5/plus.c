#include <stdio.h>
#include <stdlib.h>

char *mallocCharBySize(int size) {
    return (char *) malloc(sizeof(char) * size);
}

char *reallocCharBySize(char *ptr, int size) {
    return (char *) realloc(ptr, sizeof(char) * size);
}

int getInput(char **ptrArr) {
    int countSize = 1;
    while (1) {
        char temp = getchar();
        if (temp == '\n') 
            break;

        *(*ptrArr + (countSize - 1)) = temp;
        *ptrArr = reallocCharBySize(*ptrArr, sizeof(char) * (++countSize));
        *(*ptrArr + (countSize - 1)) = '\0';
    }
    return countSize;
}

int copyRemainValue(char **pResultArr, char *ptrArr, int pointIndex, int carry) {
    int copyValue;
    int repeat = pointIndex + 1;
    for (int i = 0; i < repeat; i++) {
        copyValue = *(ptrArr + pointIndex) - 48 + carry;

        if (copyValue >= 10) 
            carry = 1;
        else 
            carry = 0;

        *(*pResultArr + pointIndex) = copyValue % 10 + 48;

        pointIndex--;
    }
    return carry;
}

int plus(char **pResultArr, char *pNumArr1, char *pNumArr2, int sizeArr1, int sizeArr2) {
    int pointIndex1 = sizeArr1 - 2, pointIndex2 = sizeArr2 - 2, pointResultIndex; 
    int repeat;
    int carry, largerArr;
    if (sizeArr1 > sizeArr2) {
        *pResultArr = reallocCharBySize(*pResultArr, sizeArr1);
        pointResultIndex = sizeArr1 - 2;
        repeat = sizeArr2 - 1;
        largerArr = 1;
    }
    else {
        *pResultArr = reallocCharBySize(*pResultArr, sizeArr2);
        pointResultIndex = sizeArr2 - 2;
        repeat = sizeArr1 - 1;
        largerArr = 0;
    }
    *(*pResultArr + pointResultIndex + 1) = '\0';

    carry = 0;
    for (int i = 0; i < repeat; i++) {
        int sumOfTwoDigits = (*(pNumArr1 + pointIndex1) - 48) + (*(pNumArr2 + pointIndex2) - 48) + carry;
        if (sumOfTwoDigits >= 10) 
            carry = 1;
        else 
            carry = 0;

        *(*pResultArr + pointResultIndex) = (char)(sumOfTwoDigits % 10 + 48);

        pointIndex1--;
        pointIndex2--;
        pointResultIndex--;
    }
    if (largerArr) 
        carry = copyRemainValue(&*pResultArr, pNumArr1, pointIndex1, carry);
    else 
        carry = copyRemainValue(&*pResultArr, pNumArr2, pointIndex2, carry);
    return carry;
}

void displayResult(char *ptrArr, int carry) {
    if (carry) 
        printf("1%s", ptrArr);
    else
        printf("%s", ptrArr);
}

int main(void) {
    char *pNumArr1 = mallocCharBySize(1);
    char *pNumArr2 = mallocCharBySize(1);
    char *pResultArr = mallocCharBySize(1);
    int sizeArr1 = getInput(&pNumArr1);
    int sizeArr2 = getInput(&pNumArr2);
    int carry;
    carry = plus(&pResultArr, pNumArr1, pNumArr2, sizeArr1, sizeArr2);
    displayResult(pResultArr, carry);
    free(pNumArr1);
    free(pNumArr2);
    free(pResultArr);
    return 0;
}
