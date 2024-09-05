#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "date.h"

typedef struct {
    int AppointmentID;
    int DoctorID;
    int PatientID;
    Date DateOfAppointment;
    int Time;
} Appointment;



#endif 