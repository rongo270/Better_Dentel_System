#include "Patient.h";
#include <stdio.h>
#include <stdlib.h>
#include "Doctor.h";
#include "WriteBinery.h"


void log_in(Patient** patients, Doctor** doctors);


void sign_up(Patient** patients,Doctor** doctors) {
	const int Max_Len = 50;
	const int Min_Password_Len = 3;
	const int Min_Name_Len = 1;
	const int numberOfAppointments = 0;


	int id, day, month, year;
	bool check = false;
	char* password = (char*)malloc(Max_Len * sizeof(char));
	char* name = (char*)malloc(Max_Len * sizeof(char));
	char date[11];

	Date DateOfBirth;


	//ID Chack
	printf("\n enter your ID (4 DIGIT NUMBER): ");
	while (!check) {
		//printf("\n enter your ID without Check digit: ");
		scanf_s("%d", &id);
		if (id > 999 && id < 10000) {
			if (!IDcheck(patients, id)) {
				check = true;
			}
			else {
				printf("\npatient exists, plz enter a new ID: ");
			}
		}
		else {
			printf("\nid needs to be a 4 digit number, plz enter again: ");
		}
	}

	check = false;

	//Password Chack
	while (!check) {
		printf("\nenter a password (more then 4 letters): ");
		scanf_s("%s", password, Max_Len);

		if (strlen(password) > Min_Password_Len) {
			check = true;
		}
		else {
			printf("\npassword too short please enter again: ");
		}
	}

	check = false;

	//Name check
	while (!check) {
		printf("\nenter your name: ");
		scanf_s("%s", name, Max_Len);

		if (strlen(name) > Min_Name_Len) {
			check = true;
		}
		else {
			printf("\nname too short please enter again: ");
		}
	}

	check = false;

	//DateChack
	while (!check) {
		printf("\nplease enter your date of birth like this DD/MM/YYYY: ");
		scanf_s("%10s", date, (unsigned)_countof(date));
		if (sscanf_s(date, "%d/%d/%d", &day, &month, &year) == 3) {
			if (ValidateDate(month, day)) {
				DateOfBirth.day = day;
				DateOfBirth.month = month;
				DateOfBirth.year = year;
				check = true;
			}
			else {
				printf("invalidate date, please enter again: ");
			}
		}
	}

	Patient* newPatient = (Patient*)malloc(sizeof(Patient));
	init_patient(newPatient, id, password, name, DateOfBirth);
	AddPatient(&patients, newPatient);
	printf("iddddd isss -- %d", patients[1]->userInfo.ID);
	free(password);
	free(name);
	printf("Patient Made sucssfuly\n");
	WriteBinaryFile(doctors, patients);
	log_in(patients, doctors);
	
}