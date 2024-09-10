#include "doctor.h"
#include <stdlib.h>

void init_doctor(Doctor* doctor, int id, const char* password, const char* name, Date dob) {
    init_user(&(doctor->userInfo), id, password, name, dob);
    doctor->patientList = NULL;
    doctor->PatientCounter = 0;
}


void EnterPatient(Doctor* doctor, int patientID) {
    //Create a new PatientList node
    PatientList* newPatient = createPatientList(patientID);
    if (newPatient == NULL) {
        return; //Memory allocation failed
    }

    //If the doctor patient list is empty, assign the new patient as the head
    if (doctor->patientList == NULL) {
        doctor->patientList = newPatient;
        doctor->PatientCounter++;
        return;
    }

    PatientList* current = doctor->patientList;
    while (current != NULL) {
        if (current->patientID == patientID) {
            //Patient exists so leave
            free(newPatient);
            return;
        }

        //Move until NULL
        if (current->Next == NULL) {
            current->Next = newPatient;//if he is in the end, insert the Patient
            newPatient->Before = current;
            doctor->PatientCounter++;
            return;
        }
        current = current->Next;
    }
}
