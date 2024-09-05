#include <stdio.h>
#include "Doctor.h"
#include <stdlib.h>
#include "Text_Appointments.h"

void Patientmenu();
//void PrintString(const char* str);
//void PrintStringArray(char** strArray);
//void PrintAllAppointments(Patient* currentPatient);
//void ScheduleNewAppointment(Patient* currentPatient, Doctor** doctors);
//void cancelAppointment(Patient* currentPatient, Doctor** doctors);
//void buildFile(Patient currentPatient);
void log_in(Patient** patients, Doctor** doctors);

void PatientPage(Patient* currentPatient, Doctor** doctors, Patient** paitnets) {
    int choice = 0;
    int count = 0;
    char* details;
    printf("welcome to the Patient menu %s\n", currentPatient->userInfo.Name);
    Patientmenu();
    while (choice != 6)
    {
        if (count == 3) {
            Patientmenu();
            count = 0;
        }
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
           // details = ViewPatientDetails(currentPatient);
           // PrintString(details);
           // free(details);
            //details = 
            //PrintString(ViewPatientDetails(currentPatient));
            break;

        case 2:
            //PrintAllAppointments(currentPatient);
            break;

        case 3:
            //ScheduleNewAppointment(currentPatient, doctors);
            break;

        case 4:
           // cancelAppointment(currentPatient, doctors);
            break;

        case 5:
            //buildFile(*currentPatient);
            break;

        case 6:
            log_in(paitnets, doctors);
            break;

        default:
            //printf("Invalid choice. Please select a valid option.\n");
            break;
        }
        count++;
        printf("\nplase enter another number:");
    }


}

void Patientmenu() {
    printf("\n1. View Details\n");
    printf("2. View Appointments\n");
    printf("3. Schedule Appointment\n");
    printf("4. Cancel Appointment\n");
    printf("5. Print Appintments File\n");
    printf("6. Log out\n");
}
