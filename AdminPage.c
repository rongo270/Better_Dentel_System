#include <stdio.h>
#include "Doctor.h"


//#define ATTRIBUTE_ID 1
//#define ATTRIBUTE_NAME 2
//#define ATTRIBUTE_PASSWORD 3
//#define ATTRIBUTE_DOB 4

void Adminmenu();
//void* SortAndPrint(Patient** patients, Doctor** doctors, int attributeNum);

void AdminPage(Patient** patients, Doctor** doctors) {
	printf("welcome to the admin page\n");
	Adminmenu();






}
void Adminmenu() {
	printf("1. Print All Users\n");
	printf("2. Sort All Users\n");
	printf("3. Search All Users\n");
	printf("6. Log out\n");
	printf("Your choice is: ");
}
