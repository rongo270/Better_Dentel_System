#define _CRT_SECURE_NO_WARNINGS
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_user(User* user, int id, const char* password, const char* name, Date dob) {
    user->ID = id;
    user->Password = _strdup(password);
    user->Name = _strdup(name);
    user->DOB = dob;
    user->Appointments = NULL;
    user->numberOfAppointments = 0;
}


char* user_details_to_string(const User* user) {
    //Data of birth to string
    char* dobString = ToString(user->DOB);
    if (dobString == NULL) {
        return NULL; //Memory fail
    }

    //Fine buffer size
    int size = snprintf(NULL, 0, "ID: %d, Password: %s, Name: %s, Date of Birth: %s\n",
        user->ID, user->Password, user->Name, dobString);

    char* result = (char*)malloc(size + 1);

    if (result == NULL) {
        return NULL; //Memory fails
    }

    sprintf(result, "ID: %d, Password: %s, Name: %s, Date of Birth: %s\n",
        user->ID, user->Password, user->Name, dobString);

    free(dobString);

    return result;
}


void delete_appointment(User* currentUser, int appointID) {
    int found = -1;

    //Search the appointment with the appointID
    for (int i = 0; i < currentUser->numberOfAppointments; i++) {
        if (currentUser->Appointments[i]->AppointmentID == appointID) {
            found = i;
            break;
        }
    }

    // if not found
    if (found == -1) {
        printf("Appointment with ID %d not found.\n", appointID);
        return;
    }

    //Only 1 appointment free and set to NULL
    if (currentUser->numberOfAppointments == 1) {
        free(currentUser->Appointments[0]);
        free(currentUser->Appointments);
        currentUser->Appointments = NULL;
        currentUser->numberOfAppointments = 0;
    }
    else {//delete what was found and move the others
        free(currentUser->Appointments[found]);

        //Move
        for (int i = found; i < currentUser->numberOfAppointments - 1; i++) {
            currentUser->Appointments[i] = currentUser->Appointments[i + 1];
        }

        //realloc the space
        currentUser->Appointments = realloc(currentUser->Appointments, sizeof(Appointment*) * (currentUser->numberOfAppointments - 1));

        if (currentUser->Appointments == NULL && currentUser->numberOfAppointments > 1) {
            printf("Error relloc memory.\n");
            return;
        }

        currentUser->numberOfAppointments--;
    }
}

char** show_appointments(User* currentUser) {
    if (currentUser->Appointments != NULL && currentUser->numberOfAppointments > 0) {
        //Make space for appointments string
        char** AppointmentsDetiles = (char**)malloc(currentUser->numberOfAppointments * sizeof(char*));
        if (AppointmentsDetiles == NULL) {
            //Memory fails
            return NULL;
        }

        for (int i = 0; i < currentUser->numberOfAppointments; i++) {
            AppointmentsDetiles[i] = ToStringAppointment(currentUser->Appointments[i]);//Put in the array
            AppointmentsDetiles[i + 1] = NULL;//Makes the next NULL (alot of problems i had with that
            if (AppointmentsDetiles[i] == NULL) {
                for (int j = 0; j < i + 1; j++) {
                    free(AppointmentsDetiles[j]);
                }
                free(AppointmentsDetiles);
                return NULL;
            }
        }
        return AppointmentsDetiles;
    }
    return NULL;
}

bool TimeIsClear(User* currentUser, Date date, int time) {
    if (currentUser->Appointments != NULL) {//check if the appintment time is equel to another time
        for (int i = 0; (currentUser->Appointments[i] != NULL && i < currentUser->numberOfAppointments); i++) {
            if (currentUser->Appointments[i]->DateOfAppointment.year == date.year &&
                currentUser->Appointments[i]->DateOfAppointment.day == date.day &&
                currentUser->Appointments[i]->Time == time &&
                currentUser->Appointments[i]->DateOfAppointment.month == date.month) {
                return false;
            }
        }
    }
    return true;

}

bool EnterAppointment(User* user, Appointment* appointment) {
    User** newAppoinmentArray;
    if (user->numberOfAppointments != 0) {//Checks if its not the first appointment
        newAppoinmentArray = (User**)realloc(user->Appointments, (user->numberOfAppointments + 1) * sizeof(Appointment*));
    }
    else {
        newAppoinmentArray = (User**)malloc(sizeof(Appointment**));
    }
    if (newAppoinmentArray == NULL) {
        //memory check
        return false;
        return;
    }

    user->Appointments = newAppoinmentArray;

    user->Appointments[user->numberOfAppointments] = appointment;//Puts the new appointment last

    user->numberOfAppointments = user->numberOfAppointments + 1;
    
    return true;
}

void CancelAppointments(User* user, int appointID) {
    if (user == NULL || user->numberOfAppointments == 0) {
        return;
    }

    int place = -1;//Find the place with the ID in the array
    for (int i = 0; i < user->numberOfAppointments; i++) {
        if (user->Appointments[i]->AppointmentID == appointID) {
            place = i;
            break;
        }
    }

    if (place == -1) {
        return;//not found
    }

    free(user->Appointments[place]);

    for (int i = place; i < user->numberOfAppointments - 1; i++) {//Move the appointment after it was found one step before
        user->Appointments[place] = user->Appointments[user->numberOfAppointments - 1];
    }

    user->numberOfAppointments--;

    //Resize the appointments array or free it if not appointment found
    if (user->numberOfAppointments > 0) {
        Appointment** temp = (Appointment**)realloc(user->Appointments, user->numberOfAppointments * sizeof(Appointment*));
        if (temp == NULL) {
            //Memory fails
            return;
        }
        user->Appointments = temp;
    }
    else {
        //If no appointments left, set it to NULL
        user->Appointments[0] = NULL;
    }
}