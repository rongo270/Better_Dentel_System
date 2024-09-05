#ifndef PATIENT_H
#define PATIENT_H

#include "user.h"

// Patient struct inherits from User
typedef struct {
    User userInfo;  // Common user details, including Appointments
} Patient;

void init_patient(Patient* patient, int id, const char* password, const char* name, Date dob);
bool IDcheck(Patient** patients, int ID);
void AddPatient(Patient** patients, Patient* newPatient);


#endif
