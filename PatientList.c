#include "PatientList.h"
#include <stdlib.h>

PatientList* createPatientList(int patientID){

    PatientList* newNode = (PatientList*)malloc(sizeof(PatientList));
    if (newNode == NULL) {
        return NULL; // Memory allocation failed
    }

    newNode->patientID = patientID; // Directly assign the appointment pointer
    newNode->Before = NULL;
    newNode->Next = NULL;

    return newNode;
}