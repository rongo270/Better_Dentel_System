#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_user(User* user, int id, const char* password, const char* name, Date dob) {
    user->ID = id;
    user->Password = strdup(password);  // Dynamically allocate memory for the password
    user->Name = strdup(name);  // Dynamically allocate memory for the name
    user->DOB = dob;
    user->Appointments = NULL;
    user->numberOfAppointments = 0;
}

void add_appointment(User* user, Appointment* appointment) {
    user->numberOfAppointments++;
    user->Appointments = realloc(user->Appointments, sizeof(Appointment*) * user->numberOfAppointments);
    user->Appointments[user->numberOfAppointments - 1] = appointment;
}

void free_user(User* user) {
    free(user->Password);
    free(user->Name);
    for (int i = 0; i < user->numberOfAppointments; i++) {
        free(user->Appointments[i]);
    }
    free(user->Appointments);
}
