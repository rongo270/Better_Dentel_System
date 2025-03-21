#include <stdio.h>
#include <stdlib.h>

#include "Text_Appointments.h"
#include "User.h"
#include "Doctor.h"
#include "WriteBinery.h"

void Patientmenu();
void PrintString(const char* str);
void PrintStringArray(char** strArray);
void PrintAllAppointments(User* currentUser);
void ScheduleNewAppointment(Patient* currentPatient, Doctor** doctors);
void cancelAppointment(Patient* currentPatient, Doctor** doctors);
void buildFile(User currentUser);
void log_in(Patient** patients, Doctor** doctors);

void PatientPage(Patient* currentPatient, Doctor** doctors, Patient** patients) {
   
    int choice = 0;
    int count = 0;

    char* details;


    printf("welcome to the Patient menu %s\n", currentPatient->userInfo.Name);

    Patientmenu();

    while (choice != 6)
    {
        if (count == 3) {//Every 3 tesks it will print menu again
            Patientmenu();
            count = 0;
        }

        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            details = user_details_to_string(currentPatient);//Makes a string of details
            PrintString(details);
            free(details);
            break;

        case 2:
            PrintAllAppointments(currentPatient);
            break;

        case 3:
            ScheduleNewAppointment(currentPatient, doctors);
            WriteBinaryFile(doctors, patients);//Update
            break;

        case 4:
           cancelAppointment(currentPatient, doctors);
           WriteBinaryFile(doctors, patients);//Update
            break;

        case 5:
            buildFile(currentPatient->userInfo);
            break;

        case 6:
            log_in(patients, doctors);//Goes back to log in
            break;

        default:

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

void PrintString(const char* str) {//Print String
    if (str != NULL) {
        printf("%s\n", str);
    }
    else {
        printf("empty\n");
    }
}

void PrintStringArray(char** strArray) {//Print array of strings
    if (strArray == NULL) {
        printf("Array is empty.\n");
        return;
    }

    for (int i = 0; strArray[i] != NULL; i++) {
        if (strArray[i] != NULL) {
            PrintString(strArray[i]);
        }
    }
}

void PrintAllAppointments(User* currentUser) {
    char** appointmentsChar;
    appointmentsChar = show_appointments(currentUser);//Makes array of appointments strings
    PrintStringArray(appointmentsChar);
    if (appointmentsChar != NULL) {
        for (int i = 0; i < currentUser->numberOfAppointments; i++) {
            free(appointmentsChar[i]);
        }
    }
}

void ScheduleNewAppointment(Patient* currentPatient, Doctor** doctors) {
    int year, month, day, time, docNum;
    bool check = false;
    printf("Which docotor would you like to make an appointment with? (write the number)\n");
    int in = 0;
    while (in < 3) {//Print all the doctors
        printf("%d. %s\n", in + 1, doctors[in]->userInfo.Name);
        in++;
    }
    while (!check) {
        scanf_s("%d", &docNum);
        if (docNum > in + 1 || docNum < 1) {//Check if valiad
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
        scanf_s("%d %d %d", &year, &month, &day);//Scan date

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
            if (TimeIsClear(selectedDoctor, selectedDate, time)) {//Check if doctor and patient dont have an 
                if (TimeIsClear(currentPatient, selectedDate, time)) {//appointment in the same time

                    Appointment* newAppointment = CreateAppointment(selectedDoctor->userInfo.ID, currentPatient->userInfo.ID, selectedDate, time);// Creat appointment
                    if (EnterAppointment(currentPatient, newAppointment) && EnterAppointment(selectedDoctor, newAppointment)) {//Enter appointment
                        EnterPatient(selectedDoctor, currentPatient->userInfo.ID);//Enter patient to the list
                        printf("appointment was created sucssfuly");
                        check = true;
                    }
                    else {
                        printf("error got made while entering the appointments");
                        printf("\nInvalid time, enter again (0-23): ");
                        check = true;
                    }
                }
                else {
                    printf("you already have an appointment in that data and time\n");
                    printf("\nInvalid time, enter again (0-23): ");
                }
            }
            else {
                printf("the doctor already have an appointment in that data and time");
                printf("\nInvalid time, enter again (0-23): ");
            }
        }
    }
}

void cancelAppointment(Patient* currentPatient, Doctor** doctors) {
    if (currentPatient->userInfo.numberOfAppointments != 0) {//Check if has appointments
        int number, appointID;
        for (int i = 0; i < currentPatient->userInfo.numberOfAppointments; i++) {//Print all appointments
            printf("%d. %s\n", i + 1, ToStringAppointment(currentPatient->userInfo.Appointments[i]));
        }
        printf("enter the number of the appointment you wish to cancel: ");
        scanf_s("%d", &number);
        while (number < 1 || number > currentPatient->userInfo.numberOfAppointments) {
            printf("\nworng input, enter again: ");
            scanf_s("%d", &number);
        }
        appointID = currentPatient->userInfo.Appointments[number - 1]->AppointmentID;
        for (int i = 0; doctors[i] != NULL; i++) {//Search the doctor
            if (doctors[i]->userInfo.ID == currentPatient->userInfo.Appointments[number - 1]->DoctorID) {
                delete_appointment(doctors[i], appointID);//DELETE
                break;
            }
        }
        delete_appointment(currentPatient, appointID);
    }
    else {
        printf("no appointment to cancel");
    }
}

void buildFile(User currentUser) {//Build file
    if (currentUser.numberOfAppointments != 0) {
        const int Max_Len = 50;
        char* nameOfFile = (char*)malloc(Max_Len * sizeof(char));  // Allocate memory for the file name

        if (nameOfFile == NULL) {
            perror("Failed to allocate memory for file name");
            return; // Exit if memory allocation fails
        }

        printf("Enter the name of the file you wish to have: ");
        scanf_s("%s", nameOfFile, Max_Len);
        CreatAndPrint(currentUser, nameOfFile);

        free(nameOfFile); // Free the allocated memory
    }
    else {
        printf("\n dont have any appointment, so no file was made");
    }
}