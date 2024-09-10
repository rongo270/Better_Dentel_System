#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "patient.h"

// Function to write doctors, patients, and appointments to a binary file
void WriteBinaryFile(Doctor** doctors, Patient** patients) {
    const char* filename = "BineryCode.bin";
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to create file");
        return;
    }

    int doctorCountBinery = 0;
    int patientCountBinery = 0;

    // Count doctors
    while (doctors[doctorCountBinery] != NULL) {
        doctorCountBinery++;
    }

    // Count patients
    while (patients[patientCountBinery] != NULL) {
        patientCountBinery++;
    }

    // Write doctor and patient counts
    fwrite(&doctorCountBinery, sizeof(int), 1, file);
    fwrite(&patientCountBinery, sizeof(int), 1, file);

    // Write each doctor to the file
    for (int i = 0; i < doctorCountBinery; i++) {
        Doctor* doc = doctors[i];

        // Debug: print info being written

        // Write doctor ID
        fwrite(&doc->userInfo.ID, sizeof(int), 1, file);

        // Write doctor's name
        int docNameLen = strlen(doc->userInfo.Name) + 1;
        fwrite(&docNameLen, sizeof(int), 1, file);
        fwrite(doc->userInfo.Name, sizeof(char), docNameLen, file);

        // Write doctor's password
        int passwordLen = strlen(doc->userInfo.Password) + 1;
        fwrite(&passwordLen, sizeof(int), 1, file);
        fwrite(doc->userInfo.Password, sizeof(char), passwordLen, file);

        // Write doctor's Date of Birth (DOB)
        fwrite(&doc->userInfo.DOB, sizeof(Date), 1, file);

        // Write the number of patients the doctor has
        fwrite(&doc->PatientCounter, sizeof(int), 1, file);

        // Write each patient in the doctor's patient list
        PatientList* currentPatient = doc->patientList;
        while (currentPatient != NULL) {
            fwrite(&currentPatient->patientID, sizeof(int), 1, file);

            // Debug: print patient ID being written

            currentPatient = currentPatient->Next;
        }

        // Write the number of appointments for the doctor
        int appointmentCount = doc->userInfo.numberOfAppointments;
        fwrite(&appointmentCount, sizeof(int), 1, file);

        // Debug: print number of appointments being written

        // Write each appointment
        for (int j = 0; j < appointmentCount; j++) {
            Appointment* appointment = doc->userInfo.Appointments[j];
            fwrite(&appointment->AppointmentID, sizeof(int), 1, file);
            fwrite(&appointment->DoctorID, sizeof(int), 1, file);
            fwrite(&appointment->PatientID, sizeof(int), 1, file);
            fwrite(&appointment->DateOfAppointment, sizeof(Date), 1, file);
            fwrite(&appointment->Time, sizeof(int), 1, file);
        }
    }

    // Write each patient to the file
    for (int i = 0; i < patientCountBinery; i++) {
        Patient* pat = patients[i];

        // Write patient ID
        fwrite(&pat->userInfo.ID, sizeof(int), 1, file);

        // Debug: print patient info being written

        // Write patient's name
        int patNameLen = strlen(pat->userInfo.Name) + 1;
        fwrite(&patNameLen, sizeof(int), 1, file);
        fwrite(pat->userInfo.Name, sizeof(char), patNameLen, file);

        // Write patient's password
        int passwordLen = strlen(pat->userInfo.Password) + 1;
        fwrite(&passwordLen, sizeof(int), 1, file);
        fwrite(pat->userInfo.Password, sizeof(char), passwordLen, file);

        // Write patient's Date of Birth (DOB)
        fwrite(&pat->userInfo.DOB, sizeof(Date), 1, file);

        // Write the number of appointments for the patient
        fwrite(&pat->userInfo.numberOfAppointments, sizeof(int), 1, file);

        // Debug: print number of appointments for patient

        // Write each appointment
        for (int j = 0; j < pat->userInfo.numberOfAppointments; j++) {
            Appointment* appointment = pat->userInfo.Appointments[j];
            fwrite(&appointment->AppointmentID, sizeof(int), 1, file);
            fwrite(&appointment->DoctorID, sizeof(int), 1, file);
            fwrite(&appointment->PatientID, sizeof(int), 1, file);
            fwrite(&appointment->DateOfAppointment, sizeof(Date), 1, file);
            fwrite(&appointment->Time, sizeof(int), 1, file);
        }
    }

    fclose(file);
    printf("Data successfully written to %s\n", filename);
}
