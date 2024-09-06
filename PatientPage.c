#include <stdio.h>
#include <stdlib.h>

//#include "Patient.h"
#include "Text_Appointments.h"
#include "User.h"
#include "Doctor.h"

void Patientmenu();
void PrintString(const char* str);
void PrintStringArray(char** strArray);
void PrintAllAppointments(Patient* currentPatient);
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
            details = user_details_to_string(currentPatient);
            PrintString(details);
            free(details);
            break;

        case 2:
            PrintAllAppointments(currentPatient);
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

void PrintString(const char* str) {
    if (str != NULL) {
        printf("%s\n", str);
    }
    else {
        printf("empty\n");
    }
}

void PrintStringArray(char** strArray) {
    if (strArray == NULL) {
        printf("Array is empty.\n");
        return;
    }

    for (int i = 0; strArray[i] != NULL; i++) {
        if (strArray[i] != NULL) {
            printf("%s\n", strArray[i]);
        }
    }
}

void PrintAllAppointments(Patient* currentPatient) {
    char** appointmentsChar;
    appointmentsChar = show_appointments(currentPatient);
    PrintStringArray(appointmentsChar);
    if (appointmentsChar != NULL) {
        for (int i = 0; i < currentPatient->userInfo.numberOfAppointments; i++) {
            free(appointmentsChar[i]);  // Free each string in the array
        }
        //free(appointmentsChar);  // Free the array itself
    }
}

void ScheduleNewAppointment(Patient* currentPatient, Doctor** doctors) {
    int year, month, day, time, docNum;
    bool check = false;
    printf("Which docotor would you like to make an appointment with? (write the number)\n ");
    int i = 0;
    while (i < 3) {
        printf("%d. %s\n", i + 1, doctors[i]->userInfo.Name);
        i++;
    }
    while (!check) {
        scanf_s("%d", &docNum);
        if (docNum > i + 1 || docNum < 1) {
            printf("\ninvalide number, enter again: ");
        }
        else {
            check = true;
        }
    }

    Date selectedDate;
    Doctor* selectedDoctor = doctors[docNum - 1];

    check = false;
    printf("\nPlease enter the date you wish to make the appointment (YYYY MM DD):\n");

    while (!check) {
        scanf_s("%d %d %d", &year, &month, &day);

        if (year >= 999 && year <= 9999 && ValidateDate(month, day)) {
            selectedDate.year = year;
            selectedDate.month = month;
            selectedDate.day = day;
            check = true;
        }
        else {
            printf("\nInvalid date, enter again (YYYY MM DD): ");
        }
    }

    check = false;
    printf("\nPlease enter the hour you would like to make the appointment:\n");

    while (!check) {
        scanf_s("%d", &time);

        // Check if the time is valid
        if (time >= 0 && time <= 23) {
            if ( TimeIsClear(selectedDoctor,selectedDate,time) == true) {
                printf("doctor already got a appointment in this time, please enter another time: ");
            }
            else if (TimeIsClear(currentPatient, selectedDate, time) == true) {
                printf("you already got an appointment in this time, please enter another time: ");
            }
            else {
                check = true;
            }
        }
        else {
            printf("\nInvalid time, enter again (0-23): ");
        }
    }

    EnterAPatient(selectedDoctor, currentPatient);
    Appointment* newAppointment = CreateAppointment(selectedDoctor->ID, currentPatient->ID, selectedDate, time);
    EnterAppointmentToDoctor(selectedDoctor, newAppointment);
    EnterAppointmentToPatient(currentPatient, newAppointment);
    printf("\n appointment was made\n");
}