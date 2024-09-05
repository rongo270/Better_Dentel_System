#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

bool ValidateDate(int month, int Day);


char* ToString(Date date);

#endif // DATE_H
