#ifndef APPOINTMENTLIST_H
#define APPOINTMENTLIST_H

#include "appointment.h"

typedef struct PatientList {
    struct PatientList* Before;
    PatientList* appointment;
    struct PatientList* Next;
} AppointmentList;

PatientList* createAppointmentList(Appointment* appointment);


#endif // APPOINTMENT_LIST_H
