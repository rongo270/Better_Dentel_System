#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

char* ToString(Date date);


bool ValidateDate(int month, int Day);

#endif
