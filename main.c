#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "User.h"
#include "BuildStart.h"
#include "WriteBinery.h"
#include "ReadBinery.h"

void log_in(Patient** patients, Doctor** doctors);


int main() {

    printf("Hello and welcome to the Dental Systems\n");

    const char* filename = "BineryCode.bin";//binery file
    FILE* file = fopen(filename, "rb");

    Doctor** doctors = NULL;
    Patient** patients = NULL;

    if (file == NULL) {//if file was not found
        printf("This is your first time here, I will now create the system data for you.\n");
        BuildStart build;
        initializeBuild(&build);//Build the first variables

        patients = build.patients;//Initial the data into the variables
        doctors = build.doctors;

        WriteBinaryFile(doctors, patients);//Make a new file with the data
    }
    else {//If file is found
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

    return 0;
}