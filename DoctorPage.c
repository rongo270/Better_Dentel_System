#include <stdlib.h>
#include <stdio.h>
#include "Doctor.h"
#include "User.h"


void Doctormenu();
void log_in(Patient** patients, Doctor** doctors);
void printList(Doctor* currentDoctor, Patient** patients);


void DoctorPage(Doctor* currentDoctor, Patient** patients, Doctor** doctors) {
    int choice = 0;
    char* details;
    char** PatientChar;
    printf("welcome to the Doctor menu %s\n", currentDoctor->userInfo.Name);
    Doctormenu();
    while (true)
    {
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            details = user_details_to_string(currentDoctor);
            PrintString(details);
            free(details);
            break;

        case 2:
            PrintAllAppointments(currentDoctor);
            break;
        case 3:
            printList(currentDoctor,patients);
            break;
        case 4:
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
    printf("2. View Appoinemnts\n");
    printf("3. Print All Patients\n");
    printf("4. Log out\n");
}

void printList(Doctor* currentDoctor, Patient** patients) {//Print the list of patient
    int counter;
    char* details;
    PatientList* header = currentDoctor->patientList;

    while (header != NULL) {
        counter = 0; 

        while (patients[counter] != NULL) {
            if (patients[counter]->userInfo.ID == header->patientID) {//Prints the details until finish
                details = user_details_to_string(patients[counter]);
                PrintString(details);
                free(details);  
                break; 
            }
            counter++; 
        }

        header = header->Next;
    }
}