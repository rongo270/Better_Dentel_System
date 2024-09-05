#define _CRT_SECURE_NO_WARNINGS
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_user(User* user, int id, const char* password, const char* name, Date dob) {
    user->ID = id;
    user->Password = _strdup(password);  // Use _strdup instead of strdup
    user->Name = _strdup(name);  // Use _strdup instead of strdup
    user->DOB = dob;
    user->Appointments = NULL;
    user->numberOfAppointments = 0;
}

void add_appointment(User* user, Appointment* appointment) {
    if (user->numberOfAppointments == 0) {
        // First appointment: use malloc
        user->Appointments = malloc(sizeof(Appointment*) * 2);  // Allocate for 1 appointment and 1 NULL slot
        if (user->Appointments == NULL) {
            printf("Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);  // Exit if memory allocation fails
        }
    }
    else {
        // Subsequent appointments: use realloc
        user->Appointments = realloc(user->Appointments, sizeof(Appointment*) * (user->numberOfAppointments + 2));
        if (user->Appointments == NULL) {
            printf("Error: Memory reallocation failed.\n");
            exit(EXIT_FAILURE);  // Exit if memory allocation fails
        }
    }

    user->Appointments[user->numberOfAppointments] = appointment;
    user->Appointments[user->numberOfAppointments + 1] = NULL;
    user->numberOfAppointments++;
}

void free_user(User* user) {
    free(user->Password);
    free(user->Name);
    for (int i = 0; i < user->numberOfAppointments; i++) {
        free(user->Appointments[i]);
    }
    free(user->Appointments);
}

char* user_details_to_string(const User* user) {
    // Convert the Date of Birth to a string
    char* dobString = ToString(user->DOB);

    // Estimate the size of the resulting string
    int size = snprintf(NULL, 0, "ID: %d\nPassword: %s\nName: %s\nDate of Birth: %s\n",
        user->ID, user->Password, user->Name, dobString);

    // Allocate memory for the resulting string (+1 for the null terminator)
    char* result = (char*)malloc(size + 1);

    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(1); // Exit if memory allocation fails
    }

    // Create the formatted string
    sprintf(result, "ID: %d\nPassword: %s\nName: %s\nDate of Birth: %s\n",
        user->ID, user->Password, user->Name, dobString);

    // Free the temporary date string
    free(dobString);

    return result;  // Return the formatted string
}


void delete_appointment(User* currentUser, int appointID) {
    int found = -1;

    // Search for the appointment with the specified appointID
    for (int i = 0; i < currentUser->numberOfAppointments; i++) {
        if (currentUser->Appointments[i]->AppointmentID == appointID) {
            found = i;
            break;
        }
    }

    // If the appointment is not found, return without doing anything
    if (found == -1) {
        printf("Appointment with ID %d not found.\n", appointID);
        return;
    }

    // If there is only one appointment, free it and set Appointments to NULL
    if (currentUser->numberOfAppointments == 1) {
        free(currentUser->Appointments[0]);
        free(currentUser->Appointments);  // Free the array itself
        currentUser->Appointments = NULL; // Set to NULL
        currentUser->numberOfAppointments = 0;
        printf("Appointment with ID %d deleted. No more appointments left.\n", appointID);
    }
    else {
        // There are multiple appointments: delete the found one and shift others
        free(currentUser->Appointments[found]);  // Free the memory of the deleted appointment

        // Shift the remaining appointments to fill the gap
        for (int i = found; i < currentUser->numberOfAppointments - 1; i++) {
            currentUser->Appointments[i] = currentUser->Appointments[i + 1];
        }

        // Resize the array to exclude the last (now empty) slot
        currentUser->Appointments = realloc(currentUser->Appointments, sizeof(Appointment*) * (currentUser->numberOfAppointments - 1));

        if (currentUser->Appointments == NULL && currentUser->numberOfAppointments > 1) {
            printf("Error reallocating memory.\n");
            exit(1);
        }

        currentUser->numberOfAppointments--;
        printf("Appointment with ID %d deleted. Remaining appointments: %d\n", appointID, currentUser->numberOfAppointments);
    }
}

char** show_appointments(User* currentUser) {
    if (currentUser->numberOfAppointments != 0) {
        char** AppointmentsDetiles = malloc(sizeof(currentUser->numberOfAppointments) * sizeof(char*));
        for (int i = 0; i < currentUser->numberOfAppointments; i++) {
            AppointmentsDetiles[i] = ToStringAppointment(currentUser->Appointments[i]);
        }
        return AppointmentsDetiles;
    }
    return NULL;

}

bool is_appoinement_in(User* currentUser, Date date, int time){
    for (int i = 0; i < currentUser->numberOfAppointments; i++) {
        if (currentUser->Appointments[i]->DateOfAppointment.year == date.year &&
            currentUser->Appointments[i]->DateOfAppointment.day == date.day &&
            currentUser->Appointments[i]->Time == time &&
            currentUser->Appointments[i]->DateOfAppointment.month == date.month) {
            return true;
        }
    }
    return false;
}