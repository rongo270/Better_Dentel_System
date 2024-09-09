#ifndef USER_H
#define USER_H

#include "Date.h"
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
char* user_details_to_string(const User* user);
void delete_appointment(User* currentUser, int appointID);
char** show_appointments(User* currentUser);
bool is_appoinement_in(User* currentUser, Date date, int time);
bool TimeIsClear(User* currentUser, Date date, int time);
bool EnterAppointment(User* user, Appointment* appointment);
void CancelAppointments(User* user, int appointID);


#endif
