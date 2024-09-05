#ifndef READ_BINERY_H
#define READ_BINERY_H

#include "Doctor.h"

typedef struct {
    Doctor** doctors;
    Patient** patients;
}ReadBinery;


int ReadBinaryFile(Doctor*** doctors, Patient*** patients);
int ReadBinaryData(Doctor*** doctors, Patient*** patients);


#endif // !READ_BINERY_H
