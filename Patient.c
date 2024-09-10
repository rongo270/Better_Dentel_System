#include "patient.h"
#include <stdlib.h>

void init_patient(Patient* patient, int id, const char* password, const char* name, Date dob) {
    init_user(&(patient->userInfo), id, password, name, dob);
}

bool IDcheck(Patient** patients, int ID) {//Check if id already exists
    if (patients != NULL) {
        for (int i = 0; patients[i] != NULL; i++) {
            if (patients[i]->userInfo.ID == ID) {//If found retirn false
                return false;
            }
        }
    }
    return false;

}

void AddPatient(Patient*** patients, Patient* newPatient) {//Add patient to list. gets an pointer to the Patient**
    if (newPatient == NULL) {
        return; //check if ok
    }

    int count = 0;
    while ((*patients)[count] != NULL) {//Finds the patients last place
        count++;
    }
    Patient** temp = (Patient**)malloc((count + 2) * sizeof(Patient*));//Creat space (could use relloc but i didnt want)
    if (temp == NULL) {
        return; //Memory check
    }

    for (int i = 0; i < count; i++) {//Insert all
        temp[i] = (*patients)[i];
    }

    temp[count] = newPatient;//Put in the new patient
    temp[count + 1] = NULL;//after is NULL
    free(*patients);
    *patients = temp;

}