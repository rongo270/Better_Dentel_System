#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Doctor.h"
#include "Patient.h"

void Adminmenu();
void log_in(Patient** patients, Doctor** doctors);
void PrintAllUsers(void** users, int userCount, void (*printFunc)(void*));
void SortAllUsers(void** users, int userCount, int (*compareFunc)(const void*, const void*));
void* SearchAllUsers(void** users, int userCount, void* key, int (*compareFunc)(const void*, const void*));

//print
void PrintDoctor(void* doctor);
void PrintPatient(void* patient);

//sort
int CompareByID(const void* a, const void* b);
int CompareByName(const void* a, const void* b);
int CompareByPassword(const void* a, const void* b);

//Search functions for by id, name or password
void* SearchByID(void** users, int userCount, int id);
void* SearchByName(void** users, int userCount, const char* name);
void* SearchByPassword(void** users, int userCount, const char* password);

void AdminPage(Patient** patients, Doctor** doctors) {
    int choice = 0;
    int doctorCount = 0, patientCount = 0;
    int userCount = 0;
    void** allUsers = NULL;

    //Count the number of doctors and patients
    while (doctors[doctorCount] != NULL) doctorCount++;
    while (patients[patientCount] != NULL) patientCount++;
    userCount = doctorCount + patientCount;

    //Combine the doctors and patients into a one big array
    allUsers = (void**)malloc(userCount * sizeof(void*));

    for (int i = 0; i < doctorCount; i++) {
        allUsers[i] = (void*)doctors[i];  //Doctor* to void*
    }
    for (int i = 0; i < patientCount; i++) {
        allUsers[doctorCount + i] = (void*)patients[i];//Cast Patient* to void*
    }

    do {
        Adminmenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1: //Print All Users
            printf("Printing all users (Doctors and Patients):\n");
            PrintAllUsers(allUsers, doctorCount, PrintDoctor);
            PrintAllUsers((void**)(allUsers + doctorCount), patientCount, PrintPatient);
            break;

        case 2: { //Sort by id name or password
            int sortChoice;
            printf("\nSort by: 1. ID 2. Name 3. Password: ");
            scanf("%d", &sortChoice);
            if (sortChoice == 1) {
                SortAllUsers(allUsers, userCount, CompareByID);
            }
            else if (sortChoice == 2) {
                SortAllUsers(allUsers, userCount, CompareByName);
            }
            else if (sortChoice == 3) {
                SortAllUsers(allUsers, userCount, CompareByPassword);
            }
            else {
                printf("Invalid choice!\n");
                break;
            }
            PrintAllUsers(allUsers, doctorCount, PrintDoctor);
            PrintAllUsers((void**)(allUsers + doctorCount), patientCount, PrintPatient);
            break;
        }

        case 3: { //Search by id name or password
            int searchChoice;
            printf("\nSearch by: 1. ID 2. Name 3. Password: ");
            scanf("%d", &searchChoice);
            void* result = NULL;

            if (searchChoice == 1) {
                int searchID;
                printf("Enter ID to search: ");
                scanf("%d", &searchID);
                result = SearchByID(allUsers, userCount, searchID);
            }
            else if (searchChoice == 2) {
                char searchName[100];
                printf("Enter Name to search: ");
                scanf("%s", searchName);
                result = SearchByName(allUsers, userCount, searchName);
            }
            else if (searchChoice == 3) {
                char searchPassword[100];
                printf("Enter Password to search: ");
                scanf("%s", searchPassword);
                result = SearchByPassword(allUsers, userCount, searchPassword);
            }
            else {
                printf("Invalid choice!\n");
                break;
            }

            if (result != NULL) {
                printf("User found:\n");
                PrintDoctor(result); 
            }
            else {
                printf("User not found.\n");
            }
            break;
        }

        case 4:
            log_in(*patients, *doctors);
            break;

        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 6);

    free(allUsers);
}

void Adminmenu() {
    printf("\n1. Print All Users\n");
    printf("2. Sort All Users by ID, Name, or Password\n");
    printf("3. Search All Users by ID, Name, or Password\n");
    printf("4. Log out\n");
    printf("Your choice is: ");
}

//Print all users
void PrintAllUsers(void** users, int userCount, void (*printFunc)(void*)) {
    for (int i = 0; i < userCount; i++) {
        printFunc(users[i]);  //Call the doctor or patient
    }
}

//Print doctor details
void PrintDoctor(void* doctor) {
    Doctor* doc = (Doctor*)doctor;  //void* to doctor*
    char* details = user_details_to_string(&(doc->userInfo));
    printf("Doctor: %s\n", details);
    free(details);
}

//Print patient details
void PrintPatient(void* patient) {
    Patient* pat = (Patient*)patient;  //void* to Patient*
    char* details = user_details_to_string(&(pat->userInfo));
    printf("Patient: %s\n", details);
    free(details);
}

//Sort users using qsort by compare function
void SortAllUsers(void** users, int userCount, int (*compareFunc)(const void*, const void*)) {
    qsort(users, userCount, sizeof(void*), compareFunc);
}

//Compare users by ID
int CompareByID(const void* a, const void* b) {
    User* userA = *(User**)a;
    User* userB = *(User**)b;
    return (userA->ID - userB->ID);
}

//Compare users by name
int CompareByName(const void* a, const void* b) {
    User* userA = *(User**)a;
    User* userB = *(User**)b;
    return strcmp(userA->Name, userB->Name);
}

//Compare users by password
int CompareByPassword(const void* a, const void* b) {
    User* userA = *(User**)a;
    User* userB = *(User**)b;
    return strcmp(userA->Password, userB->Password);
}

//Search users by ID
void* SearchByID(void** users, int userCount, int id) {
    for (int i = 0; i < userCount; i++) {
        User* user = (User*)users[i];
        if (user->ID == id) {
            return users[i];
        }
    }
    return NULL;
}

//Search users by name
void* SearchByName(void** users, int userCount, const char* name) {
    for (int i = 0; i < userCount; i++) {
        User* user = (User*)users[i];
        if (strcmp(user->Name, name) == 0) {
            return users[i];
        }
    }
    return NULL;
}

//Search users by password
void* SearchByPassword(void** users, int userCount, const char* password) {
    for (int i = 0; i < userCount; i++) {
        User* user = (User*)users[i];
        if (strcmp(user->Password, password) == 0) {
            return users[i];
        }
    }
    return NULL;
}
