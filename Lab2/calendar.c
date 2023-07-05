#include <stdio.h>
#include <string.h>

#define STARTYEAR 1990
#define WEEK 7
#define FEBUARY 1

struct day {
    char name[4];
    int index;
} days[7];

struct month {
    char name[10];
    int totalDays;
} months[12];

void setupDays() {
    strcpy(days[0].name, "Sun");
    strcpy(days[1].name, "Mon");
    strcpy(days[2].name, "Tue");
    strcpy(days[3].name, "Wed");
    strcpy(days[4].name, "Thu");
    strcpy(days[5].name, "Fri");
    strcpy(days[6].name, "Sat");
}

void setupMonths() {
    strcpy(months[0].name, "January");
    strcpy(months[1].name, "February");
    strcpy(months[2].name, "March");
    strcpy(months[3].name, "April");
    strcpy(months[4].name, "May");
    strcpy(months[5].name, "June");
    strcpy(months[6].name, "July");
    strcpy(months[7].name, "August");
    strcpy(months[8].name, "September");
    strcpy(months[9].name, "October");
    strcpy(months[10].name, "November");
    strcpy(months[11].name, "December");

    months[0].totalDays = 31;
    months[1].totalDays = 28;
    months[2].totalDays = 31;
    months[3].totalDays = 30;
    months[4].totalDays = 31;
    months[5].totalDays = 30;
    months[6].totalDays = 31;
    months[7].totalDays = 31;
    months[8].totalDays = 30;
    months[9].totalDays = 31;
    months[10].totalDays = 30;
    months[11].totalDays = 31;
}

int isLeapYear(int year) {
    if (year % 400 == 0 && year % 100 == 0) return 1;
    else if (year % 4 == 0 && year % 100 != 0) return 1;
    else return 0;
}

int calculateTotalDays(int month, int year) {
    int days = 0;
    for (int i = STARTYEAR; i < year; i++) 
        days += (isLeapYear(i)) ? 366 : 365;
        
    for (int i = 1; i <= month; i++) 
        days += (i == FEBUARY && isLeapYear(year)) ? 29 : months[i - 1].totalDays;
        
    return days;
}

void calendar(int month, int year) {
    int startDayIndex = (calculateTotalDays(month, year) + 1) % 7;
    int monthIndex = month - 1, currentColumn = startDayIndex + 1, dayRank = 1;
    printf("%s %d\n", months[monthIndex].name, year);

    for (int i = 0; i < WEEK; i++) 
        printf("%s ", days[i].name);

    printf("\n");

    for (int i = 0; i < currentColumn - 1; i++)
        printf("    ");

    for (int i = 0; i < months[monthIndex].totalDays; i++) {
        printf("%3d ", dayRank);
        if (currentColumn % 7 == 0) printf("\n");
        dayRank++;
        currentColumn++;
    }
}

int main() {
    int month, year;
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month: ");
    scanf("%d", &month);
    printf("====================\n");
    setupDays();
    setupMonths();
    calendar(month, year);
    return 0;
}