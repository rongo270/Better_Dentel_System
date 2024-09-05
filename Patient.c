#include "patient.h"
#include <stdlib.h>

void init_patient(Patient* patient, int id, const char* password, const char* name, Date dob) {
    init_user(&(patient->userInfo), id, password, name, dob);
}
