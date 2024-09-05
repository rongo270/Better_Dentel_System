#ifndef READ_BINARY_FILE_H
#define READ_BINARY_FILE_H

#include "doctor.h"
#include "patient.h"

// Define the ReadBinary struct to hold the doctors and patients arrays
typedef struct {
    Doctor** doctors;
    Patient** patients;
} ReadBinary;

// Function to read doctors, patients, and appointments from a binary file
int ReadBinaryFile(Doctor*** doctors, Patient*** patients);

#endif // READ_BINARY_FILE_H
