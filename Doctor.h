#ifndef DOCTOR_H
#define DOCTOR_H

#include "user.h"
#include "patientList.h"

// Doctor struct inherits from User
typedef struct {
    User userInfo;  // Common user details, including Appointments

    PatientList** patientList;  // List of patients specific to Doctor
    int PatientCounter;
} Doctor;

void init_doctor(Doctor* doctor, int id, const char* password, const char* name, Date dob);


#endif
