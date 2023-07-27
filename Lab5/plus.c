#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 50000

int plusLargeNumber(char number1[], char number2[], char *ptrResultNumber) {
    int smallNumberLength = strlen(number2);
    int remainBoxes = strlen(number1) - strlen(number2);
    int number1Index = strlen(number1) - 1, number2Index = strlen(number2) - 1, resIndex = strlen(number1) - 1;
    *(ptrResultNumber + resIndex + 1) = '\0';
    int sumOfTwoDigits, carry = 0;
    for (int i = 0; i < smallNumberLength; i++) {
        sumOfTwoDigits = number1[number1Index] - 48 + number2[number2Index] - 48 + carry;
        carry = 0; 
        if (sumOfTwoDigits >= 10) carry = 1;
        *(ptrResultNumber + resIndex) = (char)(sumOfTwoDigits % 10 + 48); 
        number1Index--;
        number2Index--;
        resIndex--;
    }

    for (int i = 0; i < remainBoxes; i++) {
        if (carry) {
            *(ptrResultNumber + i) = (number1[i] - 48 + carry) % 10 + 48;
            if (number1[i] - 48 + carry < 10) carry = 0; 
        }
        else
            *(ptrResultNumber + i) = number1[i];
    }   

    if (carry) return 1;
    return 0;
}

int main(void) {
    char numberS1[SIZE], numberS2[SIZE], resultNumber[SIZE + 1];
    int carry;

    scanf("%s\n", numberS1);
    scanf("%s", numberS2);
    if (strlen(numberS1) > strlen(numberS2))
        carry = plusLargeNumber(numberS1, numberS2, resultNumber);
    else
        carry = plusLargeNumber(numberS2, numberS1, resultNumber);

    if (carry)
        printf("1%s", resultNumber);
    else    
        printf("%s", resultNumber);
    return 0;
}
