#include "doctor.h"
#include <stdlib.h>

void init_doctor(Doctor* doctor, int id, const char* password, const char* name, Date dob) {
    init_user(&(doctor->userInfo), id, password, name, dob);
    doctor->patientList = NULL;
    doctor->PatientCounter = 0;
}


bool EnterPatient(Doctor* doctor, Patient* patient) {
    //can be added here TimeCheck but its been check befor enter

    PatientList* temp = createAppointmentList(patient);//new appoinmentList made
    PatientList* first = doctor->patientList;//holds header of the doctorList
    if (doctor->patientList != NULL)
    {
        PatientList* header = first;
        while (header->Next != NULL && header->Next->patient->userInfo.ID != patient->userInfo.ID)
        {
            header = header->Next;//reach the date and time that is after the date and time its sreaching
        }

        //even if its NULL it will be ok
        temp->Next = header->Next;//enter between
        temp->Before = header;

        doctor->patientList = first;

        return true;
    }
    doctor->patientList = temp;
    return false;
}

char** ShowList(Doctor currentDoctor) {
    PatientList* header = currentDoctor.patientList;
    char** newPatientsArray = NULL;
    if (header != NULL) {
        int count = 0;
    newPatientsArray = (char**)malloc((currentDoctor.PatientCounter + 1) * sizeof(char*));
    if (newPatientsArray == NULL) {
        return NULL;//memory fail
    }

        while (header!=NULL)
        {
            newPatientsArray[count] = user_details_to_string(&header->patient->userInfo);
            if (newPatientsArray[count] == NULL) {
                // Free already allocated memory in case of failure
                for (int i = 0; i < count; i++) {
                    free(newPatientsArray[i]);
                }
                free(newPatientsArray);//memory fail
                return NULL;
            }

            header = header->Next;
            count++;
        }
        newPatientsArray[count] = NULL;//make sure the list dont return again
    }
    return newPatientsArray;
}