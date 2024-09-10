#include "PatientList.h"
#include <stdlib.h>

PatientList* createPatientList(int patientID){//Creats a new List

    PatientList* newNode = (PatientList*)malloc(sizeof(PatientList));
    if (newNode == NULL) {
        return NULL; //Memory failed
    }

    newNode->patientID = patientID;
    newNode->Before = NULL;
    newNode->Next = NULL;

    return newNode;
}