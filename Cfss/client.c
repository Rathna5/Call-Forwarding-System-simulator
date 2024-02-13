#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cfss.h>
#include<user.h>
#define PATH "/home2/trainee63/GROUP1/CFSS/data/user.dat" 

UD *headUD = NULL;
UD *tailUD = NULL;
CFSS *headCFSS = NULL;
CFSS *tailCFSS = NULL;
UD *getPDetails() {
    int flag = 1;
    int temp = 0;
    UD *newUser = NULL;
    char firstName[MAX_BUFF] = {'\0'};
    char lastName[MAX_BUFF] = {'\0'};
    char password[MAX_BUFF] = {'\0'};
    char gender = '\0';
    char phoneNumber[MAX_BUFF] = {'\0'};
    int choice = 0;

    newUser = (UD *)malloc(sizeof(UD));
    if (newUser == NULL) {
        printf("\nMemory Allocation failed!");
        exit(EXIT_FAILURE);
    }

    while (flag) {
        printf("\nEnter First Name: ");
        scanf(" ");
        fgets(firstName, MAX_BUFF, stdin);
        firstName[strlen(firstName) - 1] = '\0';
        temp = checkName(firstName);
        if (temp != -1) {
            flag = 0;
        }
    }

    temp = 0;
    flag = 1;
    while (flag) {
        printf("\nEnter Last Name: ");
        scanf(" ");
        fgets(lastName, MAX_BUFF, stdin);
        lastName[strlen(lastName) - 1] = '\0';
        temp = checkName(lastName);
        if (temp != -1) {
            flag = 0;
        }
    }

    temp = 0;
    flag = 1;
    while (flag) {
        printf("\nEnter Gender(M/F): ");
        scanf(" ");
        scanf("%c", &gender);
        temp = checkGender(gender);
        if (temp != -1) {
            flag = 0;
        }
    }

    flag = 1;
    temp = 0;
    while (flag) {
        printf("\nEnter Phone Number: ");
        scanf(" ");
        fgets(phoneNumber, MAX_BUFF, stdin);
        phoneNumber[strlen(phoneNumber) - 1] = '\0';
        temp = checkPhoneNumber(phoneNumber);
        if (temp == 0) {
            flag = 0;
        } else if (temp == -2) {
            printf("\nDo you want to continue?\nPress 1 to continue or 0 to SignIn: ");
            scanf("%d", &choice);
            if (choice == 1) {
                // Do nothing, continue loop
            } else {
                return NULL;
            }
        }
    }

    printf("\nEnter Password: ");
    scanf(" ");
    fgets(password, MAX_BUFF, stdin);
    password[strlen(password) - 1] = '\0';

    strcpy(newUser->fName, firstName);
    strcpy(newUser->lName, lastName);
    strcpy(newUser->passwd, password);
    newUser->gender = gender;
    strcpy(newUser->pNumber, phoneNumber);
    newUser->next = NULL;

    return newUser;
}
void loadPDetails() {
    FILE *filePointer = NULL;
    UD tempUser;
    UD *newUser = NULL;
    int isFirstRecord = 1;

    filePointer = fopen(PATH, "r");
    if (filePointer == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    while (readUserFile(filePointer, &tempUser)) {
        newUser = (UD *)malloc(sizeof(UD));
        if (newUser == NULL) {
            printf("\nMemory allocation failed!");
            exit(EXIT_FAILURE);
        }

        // Copy data from tempUser to newUser
        strcpy(newUser->fName, tempUser.fName);
        strcpy(newUser->lName, tempUser.lName);
        strcpy(newUser->passwd, tempUser.passwd);
        newUser->uId = tempUser.uId;
        newUser->gender = tempUser.gender;
        strcpy(newUser->pNumber, tempUser.pNumber);
        newUser->next = NULL;

        if (isFirstRecord) {
            headUD = newUser;
            tailUD = newUser;
            isFirstRecord = 0;
        } else {
            tailUD->next = newUser;
            tailUD = newUser;
        }
    }

    fclose(filePointer);
}


int readUserFile(FILE *filePointer, UD *tempUser) {
    int ret = fread(tempUser, sizeof(UD), 1, filePointer);
    return ret;
}
void writePDetails() {
    UD *currentUser = headUD;
    FILE *filePointer = NULL;
    int retVal = 0;

    filePointer = fopen(PATH, "w+");
    if (filePointer == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (currentUser != NULL) {
        retVal = writeUserFile(filePointer, currentUser);
        if (retVal == 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        currentUser = currentUser->next;
    }

    fclose(filePointer);
}
int checkName(char *name) {
    if (name == NULL) {
        return 0;
    }

    int i = 0;
    int flag = 0;
    for (i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i])) {  
            printf("Name should contain only letters, no digits or special characters allowed\n");
            flag = 1;
            break;
        }
    }

    if (flag == 1) {
        return -1;
    }
    return 1;
}
int checkGender(char ch)
{
	if(ch=='M'||ch=='F'||ch=='m'||ch=='f'){
		return 0;

    	}

   	 printf("Gender can be either M or F.\n") ;
   	 return -1;
}
int checkValidPhone(char *phoneNumber) {
    int i = 0;

    /* Check if any non-digit characters are present */
    for (i = 0; i < strlen(phoneNumber); i++) {
        if (!isdigit(phoneNumber[i])) {
            printf("Phone number should not have any characters\n");
            return -1;
        }
    }

    /* Check if the phone number is exactly 10 digits */
    if (strlen(phoneNumber) != 10) {
        printf("Phone number should be of 10 digits only\n");
        return -1;
    }

    return 0;
}
int checkPhoneNumber(char *phone) {
    UD *currentUser = headUD;
    int check = 0;

    // Check if the phone number is valid
    check = checkValidPhone(phone);
    if (check == -1) {
        return -1; // Invalid phone number format
    }

    // Check if the phone number already exists in the database
    while (currentUser != NULL) {
        if (strcmp(currentUser->pNumber, phone) == 0) {
            printf("Phone number already exists\n");
            return -2; // Phone number already exists in the database
        }
        currentUser = currentUser->next;
    }

    return 0; // Phone number is valid and does not exist in the database
}
int checkSamePNumber(char *pNumber, char *number) {	
    int check = checkValidPhone(number);

    if (check == -1) {
        return -1; // Invalid phone number format
    }

    if (strcmp(pNumber, number) == 0) {
        printf("\n\nCall forwarding to own number cannot be done!\n "); 
        return -1; // Call forwarding to own number is not allowed
    }

    return 0; // Phone numbers are different, operation is valid
}


