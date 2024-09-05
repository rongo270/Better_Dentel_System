#ifndef USER_H
#define USER_H

#include "date.h"
#include "appointment.h"

// Common struct for both Doctor and Patient
typedef struct {
    int ID;
    char* Password;
    char* Name;
    Date DOB;
    Appointment** Appointments;  // Array of appointments shared by User

    int numberOfAppointments;
} User;

void init_user(User* user, int id, const char* password, const char* name, Date dob);
void add_appointment(User* user, Appointment* appointment);
void free_user(User* user);

#endif
