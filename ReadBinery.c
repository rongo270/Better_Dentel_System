#define _CRT_SECURE_NO_WARNINGS
#include "ReadBinery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//reads doctors patients, and appointments from a binary file
int ReadBinaryFile(Doctor*** doctors, Patient*** patients) {
    const char* filename = "BineryCode.bin";
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;//fails to open file
    }

    int doctorCountBinery = 0;
    int patientCountBinery = 0;

    // Declare variables
    int nameLen;           //Len of names
    int passwordLen;       //Len of passwords
    int appointmentCount;  //Len of appointments

    //Reads count
    fread(&doctorCountBinery, sizeof(int), 1, file);
    fread(&patientCountBinery, sizeof(int), 1, file);

    *doctors = (Doctor**)malloc((doctorCountBinery + 1) * sizeof(Doctor*));  // +1 for NULL 

    //Read each doctor from the file
    for (int i = 0; i < doctorCountBinery; i++) {
        (*doctors)[i] = (Doctor*)malloc(sizeof(Doctor));

        //Read doctorID
        fread(&(*doctors)[i]->userInfo.ID, sizeof(int), 1, file);

        //Read doctor name
        fread(&nameLen, sizeof(int), 1, file);
        (*doctors)[i]->userInfo.Name = (char*)malloc(nameLen * sizeof(char));
        fread((*doctors)[i]->userInfo.Name, sizeof(char), nameLen, file);

        //Read doctor password
        fread(&passwordLen, sizeof(int), 1, file);
        (*doctors)[i]->userInfo.Password = (char*)malloc(passwordLen * sizeof(char));
        fread((*doctors)[i]->userInfo.Password, sizeof(char), passwordLen, file);

        //Read doctor Date of Birth (DOB)
        fread(&(*doctors)[i]->userInfo.DOB, sizeof(Date), 1, file);

        //Read the number of patients for doctor
        fread(&(*doctors)[i]->PatientCounter, sizeof(int), 1, file);

        //Create the patient list for the doctor
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

            //Read patient ID in the list
            fread(&newPatientNode->patientID, sizeof(int), 1, file);

            tail = newPatientNode;
        }
        (*doctors)[i]->patientList = head;//do the head

        //read the number of appointments the doctor has
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
        (*doctors)[i]->userInfo.Appointments[appointmentCount] = NULL;  //ends the appointment array with NULL
    }
    (*doctors)[doctorCountBinery] = NULL;  //ends doctor array with NULL

    //do the same for the patient
    *patients = (Patient**)malloc((patientCountBinery + 1) * sizeof(Patient*));  // +1 for NULL terminator

    for (int i = 0; i < patientCountBinery; i++) {
        (*patients)[i] = (Patient*)malloc(sizeof(Patient));

        fread(&(*patients)[i]->userInfo.ID, sizeof(int), 1, file);

        fread(&nameLen, sizeof(int), 1, file);
        (*patients)[i]->userInfo.Name = (char*)malloc(nameLen * sizeof(char));
        fread((*patients)[i]->userInfo.Name, sizeof(char), nameLen, file);

        fread(&passwordLen, sizeof(int), 1, file);
        (*patients)[i]->userInfo.Password = (char*)malloc(passwordLen * sizeof(char));
        fread((*patients)[i]->userInfo.Password, sizeof(char), passwordLen, file);

        fread(&(*patients)[i]->userInfo.DOB, sizeof(Date), 1, file);

        fread(&appointmentCount, sizeof(int), 1, file);
        (*patients)[i]->userInfo.numberOfAppointments = appointmentCount;


        (*patients)[i]->userInfo.Appointments = (Appointment**)malloc((appointmentCount + 1) * sizeof(Appointment*));  // +1 for NULL

        for (int j = 0; j < appointmentCount; j++) {
            (*patients)[i]->userInfo.Appointments[j] = (Appointment*)malloc(sizeof(Appointment));
            fread(&(*patients)[i]->userInfo.Appointments[j]->AppointmentID, sizeof(int), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->DoctorID, sizeof(int), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->PatientID, sizeof(int), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->DateOfAppointment, sizeof(Date), 1, file);
            fread(&(*patients)[i]->userInfo.Appointments[j]->Time, sizeof(int), 1, file);
        }
        (*patients)[i]->userInfo.Appointments[appointmentCount] = NULL;
    }
    (*patients)[patientCountBinery] = NULL; 

    fclose(file);//close file
    return 0;
}

int ReadAppointmentID() {
    const char* filename = "AppointmentBinery.bin";
    FILE* file = fopen(filename, "rb");
    int appointmentID = 1000;//First ID

    if (file == NULL) {
        file = fopen(filename, "wb");
        if (file == NULL) {
            return -1;//Error handle
        }
        fwrite(&appointmentID, sizeof(int), 1, file);
        fclose(file);
        return appointmentID;//Return the value 1000
    }

    //If file exists
    fread(&appointmentID, sizeof(int), 1, file);
    fclose(file);

    //Increrss the ID
    appointmentID++;

    //Open the file again to write the updated ID
    file = fopen(filename, "wb");
    if (file == NULL) {
        return -1;//Error handle opening file
    }

    //Write the updated ID back to the file
    fwrite(&appointmentID, sizeof(int), 1, file);
    fclose(file);

    //Return the new appointment ID
    return appointmentID;
}
