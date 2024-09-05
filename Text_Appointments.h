#ifndef TEXT_APPOINTMENTS_H
#define TEXT_APPOINTMENTS_H

#include "Patient.h"

typedef struct {
    Patient* patient;
    char* Text_name;
} Text_Appointments;

Text_Appointments CreatAndPrint(Patient patient, char* Text_Name);



#endif // !TEXT_APPOINTMENTS_H

