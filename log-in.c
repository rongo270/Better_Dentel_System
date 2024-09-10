#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Patient.h"
#include "Doctor.h"
#include "WriteBinery.h"

void sign_up(Patient** patients, Doctor** doctorst);
void PatientPage(Patient* currantPatient, Doctor** doctors, Patient** patients);
void DoctorPage(Doctor* currentDoctor, Patient** patients, Doctor** doctors);
void AdminPage(Patient** patients, Doctor** doctors);

void log_in(Patient** patients, Doctor** doctors) {
	int count = 0;//password tryed
	int id = -1;
	char password[50];

	printf("If you wish to sign up enter 0\n");

	while (true) {
		printf("plase enter your id - ");
		scanf_s("%d", &id);

		if (id == 0) {//Sign-up
			sign_up(patients,doctors);
		}

		else if (id == 1) {//Admin check
			printf("\nplase enter the password ");
			scanf_s("%49s", password, (unsigned)_countof(password));
			if (strcmp(password, "0000") == 0) {
				system("cls");
				printf("log in complate\n");
				AdminPage(patients, doctors);
			}
			else {
				printf("\nworng password, enter a new ID: ");
			}
		}

		else {//Patients ID check
			for (int i = 0; patients[i] != NULL; i++) {
				if (patients[i]->userInfo.ID == id) {//If found
					printf("enter the password: ");
					while (count < 5) {//5 trys
						scanf_s("%49s", password, (unsigned)_countof(password));
						if (strcmp(password, patients[i]->userInfo.Password) == 0) {
							system("cls");//i think its cool
							printf("log in complate\n");
							PatientPage(patients[i], doctors, patients);//Go to Patient Page
						}
						else if (count != 5) {
							printf("\nincorrect password, enter password again: ");
						}
						else {
							printf("too many trys, going back to the log-in system");
						}
						count++;
					}
				}
			}
			if (count == 0) {//If it wans't been found in Patient, checking the Doctors
				for (int i = 0; doctors[i] != NULL; i++) {
					if (doctors[i]->userInfo.ID == id) {
						printf("enter the password: ");
						while (count < 5) {
							scanf_s("%49s", password, (unsigned)_countof(password));
							if (strcmp(password, doctors[i]->userInfo.Password) == 0) {
								system("cls");
								printf("log in complate\n");
								DoctorPage(doctors[i], patients, doctors);//Doctor Page
							}
							else if (count != 5) {
								printf("\nincorrect password, enter password again: ");
							}
							else {
								printf("too many trys, going back to the log-in system");
							}
							count++;
						}
					}
				}
			}
		}
		if (id != 0 && id != -1 && id!=1) {
			printf("id was not found\n");
		}
		count = 0;
	}

}