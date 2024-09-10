#ifndef BUILDSTART_H
#define BUILDSTART_H

#include "patient.h" 
#include "doctor.h"

typedef struct {
    Patient** patients;
    Doctor** doctors;
} BuildStart;

void initializeBuild(BuildStart* build);
void freeBuild(BuildStart* build);

#endif
