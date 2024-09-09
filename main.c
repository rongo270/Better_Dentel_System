#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "User.h"
#include "BuildStart.h"
#include "WriteBinery.h"
#include "ReadBinery.h"

void log_in(Patient** patients, Doctor** doctors);


int main() {

    printf("Hello and welcome to gggthe Dental Systemss\n");

    const char* filename = "BineryCode.bin";
    FILE* file = fopen(filename, "rb");

    Doctor** doctors = NULL;
    Patient** patients = NULL;

    if (file == NULL) {
        printf("This is your first time here, I will now create the system data for you.\n");
        BuildStart build;
        initializeBuild(&build);

        patients = build.patients;
        doctors = build.doctors;

        WriteBinaryFile(doctors, patients);
        //freeBuild(&build);
    }
    else {
        printf("Welcome back, data is now loaded from file.\n");
        fclose(file);

        if (ReadBinaryFile(&doctors, &patients) == 0) {

        }
        else {
            printf("Failed to load data from file.\n");
            return 1; // Exit with an error code
        }
    }

    log_in(patients, doctors);

    // Free the allocated memory after usage
    if (file == NULL) {
        // Free memory only if it was allocated via BuildStart
        freeBuild(&(BuildStart) { .doctors = doctors, .patients = patients });
    }
    else {
        // Free memory if loaded from file
        for (int i = 0; doctors[i] != NULL; i++) {
            free(doctors[i]->userInfo.Password);
            free(doctors[i]->userInfo.Name);
            free(doctors[i]);
        }
        free(doctors);

        for (int i = 0; patients[i] != NULL; i++) {
            free(patients[i]->userInfo.Password);
            free(patients[i]->userInfo.Name);
            free(patients[i]);
        }
        free(patients);
    }



    return 0;
}