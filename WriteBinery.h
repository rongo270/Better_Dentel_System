#ifndef WRITE_BINERY_H
#define WRITE_BINERY_H

#include "Doctor.h"

typedef struct {
    Doctor** doctors;
    Patient** patients;
}WriteBinery;

void WriteBinaryFile(Doctor** doctors, Patient** patients);


#endif // !WRITE_BINERY_H


