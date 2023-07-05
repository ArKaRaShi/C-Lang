#include <stdio.h>

struct romanDetail {
    char symbol;
    int value;
} romanNumberDetail[7];

void setupRomanNumberDetail() {
    romanNumberDetail[0].symbol = 'I';
    romanNumberDetail[0].value = 1;
    romanNumberDetail[1].symbol = 'V';
    romanNumberDetail[1].value = 5;
    romanNumberDetail[2].symbol = 'X';
    romanNumberDetail[2].value = 10;
    romanNumberDetail[3].symbol = 'L';
    romanNumberDetail[3].value = 50;
    romanNumberDetail[4].symbol = 'C';
    romanNumberDetail[4].value = 100;
    romanNumberDetail[5].symbol = 'D';
    romanNumberDetail[5].value = 500;
    romanNumberDetail[6].symbol = 'M';
    romanNumberDetail[6].value = 1000;
}

void displayTwo(char firstSymbol, char secondSymbol) {
    printf("%c%c", firstSymbol, secondSymbol);
}

void displayDynamic(char symbol, int repeat) {
    for (int i = 0; i < repeat; i++) 
        printf("%c", symbol);
}

void convertNumberToRoman(int number) {
    int quoitent;
    
    int divider = 1000, pointIndex = 6;
    while (divider > 0) {
        quoitent = number / divider;
        number = number - quoitent * divider;
        if (quoitent == 9) {
            displayTwo(romanNumberDetail[pointIndex].symbol, romanNumberDetail[pointIndex + 2].symbol);
        }
        else if (quoitent == 4) {
            displayTwo(romanNumberDetail[pointIndex].symbol, romanNumberDetail[pointIndex + 1].symbol);
        }
        else if (quoitent >= 5) {
            displayDynamic(romanNumberDetail[pointIndex + 1].symbol, 1);
            displayDynamic(romanNumberDetail[pointIndex].symbol, quoitent - 5);
        }
        else {
            displayDynamic(romanNumberDetail[pointIndex].symbol, quoitent);
        }
        
        divider = divider / 10;
        pointIndex -= 2;
    }
}

int main() {
    int n, number;
    scanf("%d", &n);
    setupRomanNumberDetail();
    for (int i = 0; i < n; i++) {
        scanf("%d", &number);
        convertNumberToRoman(number);
    }
    return 0;
}