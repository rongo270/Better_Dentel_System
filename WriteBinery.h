#ifndef WRITE_BINARY_FILE_H
#define WRITE_BINARY_FILE_H

#include "doctor.h"
#include "patient.h"

// Define the WriteBinary struct to hold the doctors and patients arrays
typedef struct {
    Doctor** doctors;
    Patient** patients;
} WriteBinary;

// Function to write doctors, patients, and appointments to a binary file
void WriteBinaryFile(Doctor** doctors, Patient** patients);

#endif // WRITE_BINARY_FILE_H
