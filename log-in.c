#include "Patient.h"
#include "Doctor.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void sign_up(Patient** patients);
void PatientPage(Patient* currantPatient, Doctor** doctors, Patient** patients);
void DoctorPage(Doctor* currentDoctor, Patient** patients, Doctor** doctors);
//void AdminPage(Patient** patients, Doctor** doctors);

void log_in(Patient** patients, Doctor** doctors) {
	int count = 0;
	int id = -1;
	char password[50];
	printf("if you wish to sign up enter 0\n");

	while (true) {
		printf("plase enter your id - ");
		scanf_s("%d", &id);

		if (id == 0) {
			sign_up(patients);
			//printf("plase enter your id - ");
			//scanf_s("%d", &id);
		}

		else if (id == 1) {//if you get wrong 1 time with the admin, you go back to log in
			scanf_s("%49s", password, (unsigned)_countof(password));
			if (strcmp(password, "0000" == 0)) {
				printf("log in complate");
				//AdminPage(patients, doctors);
			}

		}

		else {
			for (int i = 0; patients[i] != NULL; i++) {
				if (patients[i]->userInfo.ID == id) {
					printf("enter the password: ");
					while (count < 5) {
						scanf_s("%49s", password, (unsigned)_countof(password));
						if (strcmp(password, patients[i]->userInfo.Password) == 0) {
							printf("\nlog in complate\n");
							PatientPage(patients[i], doctors, patients);
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
			if (count == 0) {
				for (int i = 0; doctors[i] != NULL; i++) {
					if (doctors[i]->userInfo.ID == id) {
						printf("enter the password: ");
						while (count < 5) {
							scanf_s("%49s", password, (unsigned)_countof(password));
							if (strcmp(password, doctors[i]->userInfo.Password) == 0) {
								printf("\nlog in complate\n");
								DoctorPage(doctors[i], patients, doctors);
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
		if (id != 0 && id != -1) {
			printf("id was not found\n");
		}
		count = 0;
	}

}