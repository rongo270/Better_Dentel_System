#ifndef DOCTOR_H
#define DOCTOR_H

#include "user.h"
#include "PatientList.h"  // Make sure this includes the definition of PatientList
#include "date.h"         // Ensure Date is also included

// Doctor struct inherits from User
typedef struct {
    User userInfo;           // Common user details, including Appointments
    PatientList** patientList; // List of patients specific to Doctor
    int PatientCounter;
} Doctor;

void init_doctor(Doctor* doctor, int id, const char* password, const char* name, Date dob);
bool EnterPatient(Doctor* doctor, Patient* patient);
char** ShowList(Doctor currentDoctor);

#endif
