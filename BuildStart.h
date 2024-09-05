#ifndef BUILDSTART_H
#define BUILDSTART_H

#include "patient.h"  // Include the header for Patient
#include "doctor.h"   // Include the header for Doctor

// The BuildStart struct holds the arrays of patients and doctors
typedef struct {
    Patient** patients;   // Array of pointers to patients
    Doctor** doctors;     // Array of pointers to doctors
} BuildStart;

// Function to initialize the build with some patients and doctors
void initializeBuild(BuildStart* build);

// Function to free all allocated memory in the build
void freeBuild(BuildStart* build);

#endif // BUILDSTART_H
