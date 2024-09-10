#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "patient.h"

//write doctors, patients, and appointments to a binary file
void WriteBinaryFile(Doctor** doctors, Patient** patients) {
    const char* filename = "BineryCode.bin";
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to create file");
        return;
    }

    int doctorCountBinery = 0;
    int patientCountBinery = 0;

    //Count doctors
    while (doctors[doctorCountBinery] != NULL) {
        doctorCountBinery++;
    }

    //Count patients
    while (patients[patientCountBinery] != NULL) {
        patientCountBinery++;
    }

    //Write doctor and patient counts
    fwrite(&doctorCountBinery, sizeof(int), 1, file);
    fwrite(&patientCountBinery, sizeof(int), 1, file);

    //Write doctor to the file
    for (int i = 0; i < doctorCountBinery; i++) {
        Doctor* doc = doctors[i];

        //Write doctor ID
        fwrite(&doc->userInfo.ID, sizeof(int), 1, file);

        //Write doctor name
        int docNameLen = strlen(doc->userInfo.Name) + 1;
        fwrite(&docNameLen, sizeof(int), 1, file);
        fwrite(doc->userInfo.Name, sizeof(char), docNameLen, file);

        //Write doctor password
        int passwordLen = strlen(doc->userInfo.Password) + 1;
        fwrite(&passwordLen, sizeof(int), 1, file);
        fwrite(doc->userInfo.Password, sizeof(char), passwordLen, file);

        //Write doctor Date of Birth
        fwrite(&doc->userInfo.DOB, sizeof(Date), 1, file);

        //Write the number of patients the doctor has
        fwrite(&doc->PatientCounter, sizeof(int), 1, file);

        //Write each patient in the doctor patient list
        PatientList* currentPatient = doc->patientList;
        while (currentPatient != NULL) {
            fwrite(&currentPatient->patientID, sizeof(int), 1, file);

            currentPatient = currentPatient->Next;
        }

        //Write the number of appointments for the doctor
        int appointmentCount = doc->userInfo.numberOfAppointments;
        fwrite(&appointmentCount, sizeof(int), 1, file);

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

    //Same for patient
    for (int i = 0; i < patientCountBinery; i++) {
        Patient* pat = patients[i];

        fwrite(&pat->userInfo.ID, sizeof(int), 1, file);

        int patNameLen = strlen(pat->userInfo.Name) + 1;
        fwrite(&patNameLen, sizeof(int), 1, file);
        fwrite(pat->userInfo.Name, sizeof(char), patNameLen, file);

        int passwordLen = strlen(pat->userInfo.Password) + 1;
        fwrite(&passwordLen, sizeof(int), 1, file);
        fwrite(pat->userInfo.Password, sizeof(char), passwordLen, file);

        fwrite(&pat->userInfo.DOB, sizeof(Date), 1, file);

        fwrite(&pat->userInfo.numberOfAppointments, sizeof(int), 1, file);


        for (int j = 0; j < pat->userInfo.numberOfAppointments; j++) {
            Appointment* appointment = pat->userInfo.Appointments[j];
            fwrite(&appointment->AppointmentID, sizeof(int), 1, file);
            fwrite(&appointment->DoctorID, sizeof(int), 1, file);
            fwrite(&appointment->PatientID, sizeof(int), 1, file);
            fwrite(&appointment->DateOfAppointment, sizeof(Date), 1, file);
            fwrite(&appointment->Time, sizeof(int), 1, file);
        }
    }

    fclose(file);//Close file
    printf("Data successfully written to %s\n", filename);
}
