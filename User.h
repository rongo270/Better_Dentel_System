#ifndef USER_H
#define USER_H

#include "Date.h"
#include "appointment.h"

typedef struct {
    int ID;
    char* Password;
    char* Name;
    Date DOB;
    Appointment** Appointments;

    int numberOfAppointments;
} User;

void init_user(User* user, int id, const char* password, const char* name, Date dob);
char* user_details_to_string(const User* user);
void delete_appointment(User* currentUser, int appointID);
char** show_appointments(User* currentUser);
bool TimeIsClear(User* currentUser, Date date, int time);
bool EnterAppointment(User* user, Appointment* appointment);
void CancelAppointments(User* user, int appointID);


#endif
