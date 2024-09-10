#include "doctor.h"
#include <stdlib.h>

void init_doctor(Doctor* doctor, int id, const char* password, const char* name, Date dob) {
    init_user(&(doctor->userInfo), id, password, name, dob);
    doctor->patientList = NULL;
    doctor->PatientCounter = 0;
}


void EnterPatient(Doctor* doctor, int patientID) {
    // Create a new PatientList node
    PatientList* newPatient = createPatientList(patientID);
    if (newPatient == NULL) {
        return; // Memory allocation failed
    }

    // If the doctor's patient list is empty, assign the new patient as the head
    if (doctor->patientList == NULL) {
        doctor->patientList = newPatient;
        doctor->PatientCounter++;
        return;
    }

    // Traverse the list to check for duplicates and find the end of the list
    PatientList* current = doctor->patientList;
    while (current != NULL) {
        if (current->patientID == patientID) {
            // Patient already exists, free the newly allocated node
            free(newPatient);
            return; // No need to insert, patient is already in the list
        }

        // Move to the next node if available
        if (current->Next == NULL) {
            // We're at the end of the list, insert the new patient here
            current->Next = newPatient;
            newPatient->Before = current;
            doctor->PatientCounter++;
            return;
        }
        current = current->Next;
    }
}

//char** ShowList(Doctor currentDoctor) {
//    PatientList* header = currentDoctor.patientList;
//    char** newPatientsArray = NULL;
//    if (header != NULL) {
//        int count = 0;
//    newPatientsArray = (char**)malloc((currentDoctor.PatientCounter + 1) * sizeof(char*));
//    if (newPatientsArray == NULL) {
//        return NULL;//memory fail
//    }
//
//        while (header!=NULL)
//        {
//            newPatientsArray[count] = user_details_to_string(&header->patient->userInfo);
//            if (newPatientsArray[count] == NULL) {
//                // Free already allocated memory in case of failure
//                for (int i = 0; i < count; i++) {
//                    free(newPatientsArray[i]);
//                }
//                free(newPatientsArray);//memory fail
//                return NULL;
//            }
//
//            header = header->Next;
//            count++;
//        }
//        newPatientsArray[count] = NULL;//make sure the list dont return again
//    }
//    return newPatientsArray;
//}