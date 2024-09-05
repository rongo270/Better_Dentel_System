#include <stdlib.h>
#include <stdio.h>
#include "Doctor.h"


void Doctormenu();
void log_in(Patient** patients, Doctor** doctors);
//void PrintStringArrayDoc(char** strArray);
//void PrintStringDoc(const char* str);
//void PrintStringArray(char** strArray);


void DoctorPage(Doctor* currentDoctor, Patient** patients, Doctor** doctors) {
    int choice = 0;
    char* details;
    char** PatientChar;
    printf("welcome to the Doctor menu %s\n", currentDoctor->userInfo.Name);
    Doctormenu();
    while (choice != 5)
    {
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            //details = ViewDoctorDetails(currentDoctor);
            //PrintStringDoc(details);
            //free(details);
            break;

        case 2:
            //PatientChar = ViewPatients(currentDoctor);
            //PrintStringArrayDoc(PatientChar);
            //if (PatientChar != NULL) {
            //    for (int i = 0; PatientChar[i] != NULL; i++) {
            //        free(PatientChar[i]); // Free each string in the array
            //    }
            //    free(PatientChar); // Free the array itself
            //}
            break;
        case 3:
            log_in(patients, doctors);
            break;

        default:
            printf("Invalid choice. Please select a valid option.\n");
            break;
        }
        printf("\nplease enter another number: ");
    }
}


void Doctormenu() {
    printf("1. View Details\n");
    printf("2. View Patients\n");
    printf("3. Log out\n");
}