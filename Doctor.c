#include "doctor.h"
#include <stdlib.h>

void init_doctor(Doctor* doctor, int id, const char* password, const char* name, Date dob) {
    init_user(&(doctor->userInfo), id, password, name, dob);
    doctor->patientList = NULL;
    doctor->PatientCounter = 0;
}
