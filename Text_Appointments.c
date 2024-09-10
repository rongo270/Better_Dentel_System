#define _CRT_SECURE_NO_WARNINGS
#include "Text_Appointments.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Create a text file and print the user details and appointments
Text_Appointments CreatAndPrint(User currentUser, char* Text_Name) {
    // Initialize the Text_Appointments struct
    Text_Appointments textAppointments;
    textAppointments.currentUser = &currentUser;
    textAppointments.Text_name = Text_Name;

    //Open the file for writing
    FILE* file = fopen(textAppointments.Text_name, "a");

    if (file == NULL) {
        return textAppointments;//check if file is clear
    }

    //Write user (doctor or patient) details to the file
    fprintf(file, "User ID: %d\nName: %s\nDate of Birth: %02d/%02d/%04d\n\n",
        currentUser.ID,
        currentUser.Name,
        currentUser.DOB.day,
        currentUser.DOB.month,
        currentUser.DOB.year);

    //Write each appointment to the file
    for (int i = 0; i < currentUser.numberOfAppointments; i++) {
        char* appointmentStr = ToStringAppointment(currentUser.Appointments[i]);
        if (appointmentStr != NULL) {
            fprintf(file, "%s\n", appointmentStr);
            free(appointmentStr);  //Free the string after writing it to the file
        }
    }

    //Close the file
    fclose(file);
    return textAppointments;
}
