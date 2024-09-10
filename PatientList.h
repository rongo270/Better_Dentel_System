#ifndef PARIENTLIST_H
#define PARIENTLIST_H

#include "Patient.h"

typedef struct PatientList {
    struct PatientList* Before;
    int patientID;
    struct PatientList* Next;
} PatientList;

PatientList* createPatientList(int patientID);


#endif
