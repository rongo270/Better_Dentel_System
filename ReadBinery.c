#define _CRT_SECURE_NO_WARNINGS
#include "ReadBinery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read doctors, patients, and appointments from a binary file
int ReadBinaryFile(Doctor*** doctors, Patient*** patients) {
    const char* filename = "BineryCode.bin";
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    int doctorCountBinery = 0;
    int patientCountBinery = 0;

    // Declare variables
    int nameLen;           // To store the length of names
    int passwordLen;       // To store the length of passwords
    int appointmentCount;  // To store the number of appointments

    // Read the number of doctors and patients
    fread(&doctorCountBinery, sizeof(int), 1, file);
    fread(&patientCountBinery, sizeof(int), 1, file);

    // Allocate memory for doctors
    *doctors = (Doctor**)malloc((doctorCountBinery + 1) * sizeof(Doctor*));  // +1 for NULL terminator

    // Read each doctor from the file
    for (int i = 0; i < doctorCountBinery; i++) {
        (*doctors)[i] = (Doctor*)malloc(sizeof(Doctor));

        // Read doctor ID
        fread(&(*doctors)[i]->userInfo.ID, sizeof(int), 1, file);

        // Debug: print doctor info being read

        // Read doctor's name
        fread(&nameLen, sizeof(int), 1, file);
        (*doctors)[i]->userInfo.Name = (char*)malloc(nameLen * sizeof(char));
        fread((*doctors)[i]->userInfo.Name, sizeof(char), nameLen, file);

        // Read doctor's password
        fread(&passwordLen, sizeof(int), 1, file);
        (*doctors)[i]->userInfo.Password = (char*)malloc(passwordLen * sizeof(char));
        fread((*doctors)[i]->userInfo.Password, sizeof(char), passwordLen, file);

        // Read doctor's Date of Birth (DOB)
        fread(&(*doctors)[i]->userInfo.DOB, sizeof(Date), 1, file);

        // Read the number of patients the doctor has
        fread(&(*doctors)[i]->PatientCounter, sizeof(int), 1, file);

        // Create the patient list for the doctor
        PatientList* head = NULL;
        PatientList* tail = NULL;
        for (int j = 0; j < (*doctors)[i]->PatientCounter; j++) {
            PatientList* newPatientNode = (PatientList*)malloc(sizeof(PatientList));
            newPatientNode->Next = NULL;
            newPatientNode->Before = tail;

            if (tail != NULL) {
                tail->Next = newPatientNode;
            }
            else {
                head = newPatientNode;
            }

            // Read patient's ID in the list
            fread(&newPatientNode->patientID, sizeof(int), 1, file);

            tail = newPatientNode;
        }
        (*doctors)[i]->patientList = head;  // Assign the head of the patient list

        // Read the number of appointments the doctor has
        fread(&appointmentCount, sizeof(int), 1, file);


        (*doctors)[i]->userInfo.numberOfAppointments = appointmentCount;
        (*doctors)[i]->userInfo.Appointments = (Appointment**)malloc((appointmentCount + 1) * sizeof(Appointment*));  // +1 for NULL

        // Read each appointment
        for (int j = 0; j < appointmentCount; j++) {
            (*doctors)[i]->userInfo.Appointments[j] = (Appointment*)malloc(sizeof(Appointment));
            fread(&(*doctors)[i]->userInfo.Appointments[j]->AppointmentID, sizeof(int), 1, file);
            fread(&(*doctors)[i]->userInfo.Appointments[j]->DoctorID, sizeof(int), 1, file);
            fread(&(*doctors)[i]->userInfo.Appointments[j]->PatientID, sizeof(int), 1, file);
            fread(&(*doctors)[i]->userInfo.Appointments[j]->DateOfAppointment, sizeof(Date), 1, file);
            fread(&(*doctors)[i]->userInfo.Appointments[j]->Time, sizeof(int), 1, file);
        }
        (*doctors)[i]->userInfo.Appointments[appointmentCount] = NULL;  // Terminate the appointment array with NULL
    }
    (*doctors)[doctorCountBinery] = NULL;  // Terminate doctor array with NULL

    // Allocate memory for patients
    *patients = (Patient**)malloc((patientCountBinery + 1) * sizeof(Patient*));  // +1 for NULL terminator

    // Read each patient from the file
    for (int i = 0; i < patientCountBinery; i++) {
        (*patients)[i] = (Patient*)malloc(sizeof(Patient));

        // Read patient ID
        fread(&(*patients)[i]->userInfo.ID, sizeof(int), 1, file);


        // Read patient's name
        fread(&nameLen, sizeof(int), 1, file);
        (*patients)[i]->userInfo.Name = (char*)malloc(nameLen * sizeof(char));
        fread((*patients)[i]->userInfo.Name, sizeof(char), nameLen, file);

        // Read patient's password
        fread(&passwordLen, sizeof(int), 1, file);
        (*patients)[i]->userInfo.Password = (char*)malloc(passwordLen * sizeof(char));
        fread((*patients)[i]->userInfo.Password, sizeof(char), passwordLen, file);

        // Read patient's Date of Birth (DOB)
        fread(&(*patients)[i]->userInfo.DOB, sizeof(Date), 1, file);

        // Read the number of appointments the patient has
        fread(&appointmentCount, sizeof(int), 1, file);
        (*patients)[i]->userInfo.numberOfAppointments = appointmentCount;


        (*patients)[i]->userInfo.Appointments = (Appointment**)malloc((appointmentCount + 1) * sizeof(Appointment*));  // +1 for NULL

        // Read each appointment
        for (int j = 0; j < appointmentCount; j++) {
            (*patients)[i]->userInfo.Appointments[j] = (Appointment*)malloc(sizeof(Appointment));
            fread(&(*patients)[i]->userInfo.Appointments[j]->AppointmentID, sizeof(int), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->DoctorID, sizeof(int), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->PatientID, sizeof(int), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->DateOfAppointment, sizeof(Date), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->Time, sizeof(int), 1, file);
        }
        (*patients)[i]->userInfo.Appointments[appointmentCount] = NULL;  // Terminate the appointment array with NULL
    }
    (*patients)[patientCountBinery] = NULL;  // Terminate patient array with NULL

    fclose(file);
    return 0;
}
