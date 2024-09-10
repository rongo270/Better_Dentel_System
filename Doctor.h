#ifndef DOCTOR_H
#define DOCTOR_H

#include "user.h"
#include "PatientList.h"
#include "date.h"


typedef struct {
    User userInfo;
    PatientList* patientList;
    int PatientCounter;
} Doctor;

void init_doctor(Doctor* doctor, int id, const char* password, const char* name, Date dob);
void EnterPatient(Doctor* doctor, int patientID);

#endif
