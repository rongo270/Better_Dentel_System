#include "BuildStart.h"
#include <stdlib.h>
#include <string.h>

void initializeBuild(BuildStart* build) {
    // Initialize the patients array
    build->patients = (Patient**)malloc(1 * sizeof(Patient*));

    // Initialize the first patient
    build->patients[0] = (Patient*)malloc(sizeof(Patient));
    build->patients[0]->userInfo.ID = 1234;
    build->patients[0]->userInfo.Password = (char*)malloc(20 * sizeof(char));
    build->patients[0]->userInfo.Name = (char*)malloc(50 * sizeof(char));
    strcpy_s(build->patients[0]->userInfo.Password, 20, "1234");
    strcpy_s(build->patients[0]->userInfo.Name, 50, "RON");
    build->patients[0]->userInfo.DOB.day = 1;
    build->patients[0]->userInfo.DOB.month = 1;
    build->patients[0]->userInfo.DOB.year = 2000;
    build->patients[0]->userInfo.Appointments = NULL; // No appointments yet
    build->patients[0]->userInfo.numberOfAppointments = 0;
    build->patients[1] = NULL; // Mark the end of the patient array

    // Initialize the doctors array
    build->doctors = (Doctor**)malloc(3 * sizeof(Doctor*));

    // Initialize Doctor 1 (Dr. Golan)
    build->doctors[0] = (Doctor*)malloc(sizeof(Doctor));
    build->doctors[0]->userInfo.ID = 1111;
    build->doctors[0]->userInfo.Password = (char*)malloc(20 * sizeof(char));
    build->doctors[0]->userInfo.Name = (char*)malloc(50 * sizeof(char));
    strcpy_s(build->doctors[0]->userInfo.Password, 20, "1111");
    strcpy_s(build->doctors[0]->userInfo.Name, 50, "DR.GOLAN");
    build->doctors[0]->userInfo.DOB.day = 1;
    build->doctors[0]->userInfo.DOB.month = 1;
    build->doctors[0]->userInfo.DOB.year = 1970;
    build->doctors[0]->userInfo.Appointments = NULL;  // No appointments yet
    build->doctors[0]->userInfo.numberOfAppointments = 0;
    build->doctors[0]->patientList = NULL;   // No patients yet
    build->doctors[0]->PatientCounter = 0;

    // Initialize Doctor 2 (Dr. Rosenberg)
    build->doctors[1] = (Doctor*)malloc(sizeof(Doctor));
    build->doctors[1]->userInfo.ID = 2222;
    build->doctors[1]->userInfo.Password = (char*)malloc(20 * sizeof(char));
    build->doctors[1]->userInfo.Name = (char*)malloc(50 * sizeof(char));
    strcpy_s(build->doctors[1]->userInfo.Password, 20, "2222");
    strcpy_s(build->doctors[1]->userInfo.Name, 50, "DR.ROSENBERG");
    build->doctors[1]->userInfo.DOB.day = 2;
    build->doctors[1]->userInfo.DOB.month = 2;
    build->doctors[1]->userInfo.DOB.year = 1975;
    build->doctors[1]->userInfo.Appointments = NULL;  // No appointments yet
    build->doctors[1]->userInfo.numberOfAppointments = 0;
    build->doctors[1]->patientList = NULL;   // No patients yet
    build->doctors[1]->PatientCounter = 0;

    // Initialize Doctor 3 (Dr. Seuss)
    build->doctors[2] = (Doctor*)malloc(sizeof(Doctor));
    build->doctors[2]->userInfo.ID = 3333;
    build->doctors[2]->userInfo.Password = (char*)malloc(20 * sizeof(char));
    build->doctors[2]->userInfo.Name = (char*)malloc(50 * sizeof(char));
    strcpy_s(build->doctors[2]->userInfo.Password, 20, "3333");
    strcpy_s(build->doctors[2]->userInfo.Name, 50, "DR.SEUSS");
    build->doctors[2]->userInfo.DOB.day = 2;
    build->doctors[2]->userInfo.DOB.month = 3;
    build->doctors[2]->userInfo.DOB.year = 1904;
    build->doctors[2]->userInfo.Appointments = NULL;  // No appointments yet
    build->doctors[2]->userInfo.numberOfAppointments = 0;
    build->doctors[2]->patientList = NULL;   // No patients yet
    build->doctors[2]->PatientCounter = 0;

    //Mark the end of the doctors array
    build->doctors[3] = NULL;
}

void freeBuild(BuildStart* build) {
    //Free the patients
    if (build->patients != NULL) {
        //Free patient data
        for (int i = 0; build->patients[i] != NULL; i++) {
            free(build->patients[i]->userInfo.Password);
            free(build->patients[i]->userInfo.Name);

            //Free each patient appointments
            if (build->patients[i]->userInfo.Appointments != NULL) {
                for (int j = 0; j < build->patients[i]->userInfo.numberOfAppointments; j++) {
                    free(build->patients[i]->userInfo.Appointments[j]);
                }
                free(build->patients[i]->userInfo.Appointments);
            }

            free(build->patients[i]); //Free the patient itself
        }
        free(build->patients); //Free the patient array
    }

    //Free the doctors
    if (build->doctors != NULL) {
        //Free each doctor data
        for (int i = 0; build->doctors[i] != NULL; i++) {
            free(build->doctors[i]->userInfo.Password);
            free(build->doctors[i]->userInfo.Name);

            //Free each doctor appointments if any
            if (build->doctors[i]->userInfo.Appointments != NULL) {
                for (int j = 0; build->doctors[i]->userInfo.Appointments[j] != NULL; j++) {
                    free(build->doctors[i]->userInfo.Appointments[j]);
                }
                free(build->doctors[i]->userInfo.Appointments);
            }

            free(build->doctors[i]); //Free doctor
        }
        free(build->doctors); //Free the doctor array
    }
}
