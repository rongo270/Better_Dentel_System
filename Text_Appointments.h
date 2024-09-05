#ifndef TEXT_APPOINTMENTS_H
#define TEXT_APPOINTMENTS_H

#include "User.h"

typedef struct {
    User* currentUser;
    char* Text_name;
} Text_Appointments;

Text_Appointments CreatAndPrint(User* currentUser, char* Text_Name);



#endif // !TEXT_APPOINTMENTS_H

