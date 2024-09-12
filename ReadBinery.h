#ifndef READ_BINARY_FILE_H
#define READ_BINARY_FILE_H

#include "doctor.h"
#include "patient.h"

typedef struct {
    Doctor** doctors;
    Patient** patients;
} ReadBinary;


int ReadBinaryFile(Doctor*** doctors, Patient*** patients);
int ReadAppointmentID();

#endif 
