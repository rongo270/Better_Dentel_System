#include "patient.h"
#include <stdlib.h>

void init_patient(Patient* patient, int id, const char* password, const char* name, Date dob) {
    init_user(&(patient->userInfo), id, password, name, dob);
}

bool IDcheck(Patient** patients, int ID) {
    if (patients != NULL) {
        for (int i = 0; patients[i] != NULL; i++) {
            if (patients[i]->userInfo.ID == ID) {
                return false;
            }
        }
    }
    return false;

}

void AddPatient(Patient** patients, Patient* newPatient) {
    if (newPatient == NULL) {
        return; //check if ok
    }

    // Find the size of the patient array
    int count = 0;
    while (patients[count] != NULL) {
        count++;
    }
    Patient** temp = (Patient**)realloc(*patients, (count + 2) * sizeof(Patient*));
    if (temp == NULL) {
        return; // Memory check
    }
    *patients = temp;
    patients[count] = newPatient;
    patients[count + 1] = NULL;
}