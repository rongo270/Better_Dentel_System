#ifndef PARIENTLIST_H
#define PARIENTLIST_H

#include "Patient.h"

typedef struct PatientList {
    struct PatientList* Before;
    Patient* patient;
    struct PatientList* Next;
} PatientList;

PatientList* createAppointmentList(Appointment* appointment);


#endif // APPOINTMENT_LIST_H
