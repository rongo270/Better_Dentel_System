#include "Appointment.h"
#include <stdlib.h>


Appointment* CreateAppointment(int doctorID, int patientID, Date DOA, int time) {

    Appointment* newAppointment = (Appointment*)malloc(sizeof(Appointment));
    if (newAppointment == NULL) {//memory failure
        return NULL;
    }

    newAppointment->DoctorID = doctorID;
    newAppointment->PatientID = patientID;
    newAppointment->DateOfAppointment = DOA;
    newAppointment->Time = time;

    static int nextAppointmentID = 1; // own ID
    newAppointment->AppointmentID = nextAppointmentID++;

    return newAppointment;
}


char* ToStringAppointment(Appointment* appointment) {
    if (appointment == NULL) {
        return NULL;
    }

    // Calculate the required buffer size
    int bufferSize = snprintf(NULL, 0,
        "Appointment ID: %d,  Doctor ID: %d,  Patient ID: %d\nDate of Appointment: %02d/%02d/%04d,  Time: %02d:00\n",
        appointment->AppointmentID,
        appointment->DoctorID,
        appointment->PatientID,
        appointment->DateOfAppointment.day,
        appointment->DateOfAppointment.month,
        appointment->DateOfAppointment.year,
        appointment->Time);

    // Allocate the required memory (+1 for the null terminator)
    char* result = (char*)malloc((bufferSize + 1) * sizeof(char));
    if (result == NULL) {//memory failure
        return NULL;
    }

    // Populate the allocated buffer with the formatted string
    snprintf(result, bufferSize + 1,
        "Appointment ID: %d\nDoctor ID: %d\nPatient ID: %d\nDate of Appointment: %02d/%02d/%04d\nTime: %02d:00\n",
        appointment->AppointmentID,
        appointment->DoctorID,
        appointment->PatientID,
        appointment->DateOfAppointment.day,
        appointment->DateOfAppointment.month,
        appointment->DateOfAppointment.year,
        appointment->Time);

    return result;
}

