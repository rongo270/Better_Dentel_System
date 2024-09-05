#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Date.h"

char* ToString(Date date) {
    // Allocate memory for the resulting string (10 characters for DD/MM/YYYY + 1 for the null terminator)
    char* dateString = (char*)malloc(11 * sizeof(char)); // 10 for DD/MM/YYYY and 1 for '\0'

    if (dateString == NULL) {
        printf("Memory allocation failed.\n");
        exit(1); // Exit on memory allocation failure
    }

    // Format the date into the string
    sprintf(dateString, "%02d/%02d/%04d", date.day, date.month, date.year);

    return dateString;  // Return the formatted string
}

bool ValidateDate(int month, int day) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day<1 || day>daysInMonth[month - 1]) {
        return false;
    }
    return true;

}