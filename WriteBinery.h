#ifndef WRITE_BINARY_FILE_H
#define WRITE_BINARY_FILE_H

#include "doctor.h"
#include "patient.h"

typedef struct {
    Doctor** doctors;
    Patient** patients;
} WriteBinary;

void WriteBinaryFile(Doctor** doctors, Patient** patients);

#endif
