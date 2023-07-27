#include <stdio.h>
#include <string.h>

#define STARTYEAR 1970
#define STARTDAY 5
#define STARTMONTH 1

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
    strcpy(months[0].name, "JAN");
    strcpy(months[1].name, "FEB");
    strcpy(months[2].name, "MAR");
    strcpy(months[3].name, "APR");
    strcpy(months[4].name, "MAY");
    strcpy(months[5].name, "JUN");
    strcpy(months[6].name, "JUL");
    strcpy(months[7].name, "AUG");
    strcpy(months[8].name, "SEP");
    strcpy(months[9].name, "OCT");
    strcpy(months[10].name, "NOV");
    strcpy(months[11].name, "DEC");

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

typedef struct datetime {
    int date;
    int month;
    int year;
    int dayOfWeek;
    int hour;
    int minute; 
    int second; 
} datetime_t;

int isLeapYear(int year) {
    if (year % 400 == 0 && year % 100 == 0) return 1;
    else if (year % 4 == 0 && year % 100 != 0) return 1;
    else return 0;
}

datetime_t createDate(int timestamp) {
    setupDays();
    setupMonths();
    datetime_t dateInformation;

    int secondsInOneDay = 60 * 60 * 24;
    int currSeconds = 0;
    int currDay = 1, currMonth = STARTMONTH, currYear = STARTYEAR;
    int totalDays = STARTDAY;

    while (currSeconds + secondsInOneDay < timestamp) {
        currSeconds += secondsInOneDay;
        currDay++;
        totalDays++;

        if (currDay > months[currMonth - 1].totalDays) {
            currDay = 1;
            currMonth++;
        }

        if (currMonth > 12) {
            currMonth = 1;
            currYear++;
            months[1].totalDays = (isLeapYear(currYear)) ? 29 : 28;
        }
    }

    timestamp = timestamp - (totalDays - STARTDAY) * secondsInOneDay;

    dateInformation.hour = timestamp / (60 * 60);
    dateInformation.minute = (timestamp % (60 * 60)) / 60;
    dateInformation.second = timestamp % (60 * 60) % 60;
    dateInformation.date = currDay;
    dateInformation.dayOfWeek = (totalDays - 1) % 7 + 1;
    dateInformation.month = currMonth;
    dateInformation.year = currYear;

    return dateInformation;
}
void printDate(datetime_t dateInformation) {
    printf("%s %d %s %d %02d:%02d:%02d",
    days[dateInformation.dayOfWeek - 1].name,
    dateInformation.date,
    months[dateInformation.month - 1].name,
    dateInformation.year,
    dateInformation.hour,
    dateInformation.minute,
    dateInformation.second);
}

int main(void) {
    datetime_t inputDate;
    int timestamp;
    scanf("%d", &timestamp);
    inputDate = createDate(timestamp);
    printDate(inputDate);
    return 0;
}