#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Date.h"


char* ToString(Date dob) {
    //Memory for the date string DD/MM/YYYY and NULL
    char* dobString = (char*)malloc(11 * sizeof(char));
    if (dobString == NULL) {
        return NULL; //Memory failure
    }

    //Format the date as a string
    snprintf(dobString, 11, "%02d/%02d/%04d", dob.day, dob.month, dob.year);

    return dobString;  //Return dynamically allocated string
}

bool ValidateDate(int month, int day) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day<1 || day>daysInMonth[month - 1]) {
        return false;
    }
    return true;

}