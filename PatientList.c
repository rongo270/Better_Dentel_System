#include "PatientList.h"
#include <stdlib.h>

PatientList* createAppointmentList(Patient* patient) {

    PatientList* newNode = (PatientList*)malloc(sizeof(PatientList));
    if (newNode == NULL) {
        return NULL; // Memory allocation failed
    }

    newNode->patient = patient; // Directly assign the appointment pointer
    newNode->Before = NULL;
    newNode->Next = NULL;

    return newNode;
}