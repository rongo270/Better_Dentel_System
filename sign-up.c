#include "Patient.h";
#include <stdio.h>
#include <stdlib.h>
#include "Doctor.h";
#include "WriteBinery.h"


void log_in(Patient** patients, Doctor** doctors);


void sign_up(Patient** patients,Doctor** doctors) {
	const int Max_Len = 50;//Max len of an password and name
	const int Min_Password_Len = 3;//Min len of an password
	const int Min_Name_Len = 1;//Min name len


	int id, day, month, year; //Data variables
	bool check = false;
	char* password = (char*)malloc(Max_Len * sizeof(char));
	char* name = (char*)malloc(Max_Len * sizeof(char));
	char date[11];

	Date DateOfBirth;


	//ID Chack
	printf("\n enter your ID (4 DIGIT NUMBER): ");
	while (!check) {
		scanf_s("%d", &id);
		if (id > 999 && id < 10000) {
			if (!IDcheck(patients, id)){//Check if exist another same ID
				check = true;
			}
			else {
				printf("\npatient exists, plz enter a new ID: ");//Exaption
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
		if (sscanf_s(date, "%d/%d/%d", &day, &month, &year) == 3) {//Cool trick i saw
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

	Patient* newPatient = (Patient*)malloc(sizeof(Patient));//Give space for a newPatient
	init_patient(newPatient, id, password, name, DateOfBirth);//Make new Patient
	AddPatient(&patients, newPatient);//add the patient into the patients array
	free(password);
	free(name);
	printf("Patient Made sucssfuly\n");
	WriteBinaryFile(doctors, patients);//update
	log_in(patients, doctors);//Goes back to log in
	
}