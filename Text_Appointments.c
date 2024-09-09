#define _CRT_SECURE_NO_WARNINGS
#include "Text_Appointments.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a text file and print the user details and appointments
Text_Appointments CreatAndPrint(User currentUser, char* Text_Name) {
    // Initialize the Text_Appointments struct
    Text_Appointments textAppointments;
    textAppointments.currentUser = &currentUser;
    textAppointments.Text_name = Text_Name;

    // Create and open the file for writing (append mode)
    FILE* file = fopen(textAppointments.Text_name, "a");

    if (file == NULL) {
        perror("Failed to open file for writing");
        return textAppointments;  // Return the struct even in case of an error
    }

    // Write user (doctor or patient) details to the file
    fprintf(file, "User ID: %d\nName: %s\nDate of Birth: %02d/%02d/%04d\n\n",
        currentUser.ID,
        currentUser.Name,
        currentUser.DOB.day,
        currentUser.DOB.month,
        currentUser.DOB.year);

    // Write each appointment to the file (if any)
    for (int i = 0; i < currentUser.numberOfAppointments; i++) {
        char* appointmentStr = ToStringAppointment(currentUser.Appointments[i]);
        if (appointmentStr != NULL) {
            fprintf(file, "%s\n", appointmentStr);
            free(appointmentStr);  // Free the string after writing it to the file
        }
    }

    // Close the file
    fclose(file);
    return textAppointments;
}
