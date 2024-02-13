#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<common.h>
#include<user.h>
#include<cfss.h>
extern UD *headUD;
extern UD *tailUD;
extern CFSS *headCFSS;
extern CFSS *tailCFSS;

void signUp() {
    UD *newUser = NULL;

    newUser = getPDetails();

    if (newUser == NULL) {
        return;
    } else {
        if (headUD == NULL) {
            newUser->uId = 1;
            headUD = newUser;
            tailUD = newUser;
        } else {
            newUser->uId = (tailUD->uId) + 1;
            tailUD->next = newUser;
            tailUD = newUser;
        }

        addCfss(newUser->uId);
        printf("\nYou have been registered successfully!\n\n");
    }
}

int signIn() {
    char phoneNumber[MAX_BUFF] = {'\0'};
    char password[MAX_BUFF] = {'\0'};
    int userId = 0;

    printf("\nEnter phone number: ");
    scanf(" ");
    fgets(phoneNumber, MAX_BUFF, stdin);
    phoneNumber[strlen(phoneNumber) - 1] = '\0';

    printf("\nEnter Password: ");
    scanf(" ");
    fgets(password, MAX_BUFF, stdin);
    password[strlen(password) - 1] = '\0';

    userId = checkCred(phoneNumber, password);

    if (userId > 0) {
        printf("\nLogged In Successfully!\n\n");
        return userId;
    }

    printf("\nEither Phone number or Password is Incorrect! Try Again.\n\n");
    return -1;
}

int checkCred(char *phoneNumber, char *password) {
    int flag = 0;
    int userId = 0;
    UD *currentNode = headUD;

    while (currentNode != NULL) {
        if (strcmp(currentNode->pNumber, phoneNumber) == 0) {
            flag += 1;
            if (strcmp(currentNode->passwd, password) == 0) {
                flag += 1;
                userId = currentNode->uId;
                break;
            } else {
                break;
            }
        }
        currentNode = currentNode->next;
    }

    if (flag == 2) {
        return userId;
    }
    
    return 0;
}

int initialScreen() {
    int choice = 0;

    system("clear");
    printf("*******************Welcome To Call Forwarding System Simulator*********************\n\n");
    printf("Press:\n");
    printf("1. To SignUp\n");
    printf("2. To SignIn\n");
    printf("3. To Exit\n\n");
    printf("***********************************************************************************\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int mainScreen(char *firstName) {
    int choice = 0;
    system("clear");

    printf("***********************Welcome, %s****************************\n\n", firstName);
    printf("Press:\n");
    printf("1. To Activate Call Forwarding Service\n");
    printf("2. To Deactivate Call Forwarding Service\n");
    printf("3. To Unregister\n");
    printf("4. Make a call\n");
    printf("5. Log Out\n");
    printf("6. Exit Application\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int cfsScreen() {
    int choice = 0;

    system("clear");
    printf("Press,\n");
    printf("1. Unconditional\n");
    printf("2. No Reply\n");
    printf("3. Busy\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void searchUser(int userId, char *firstName) {
    UD *currentNode = headUD;

    while (currentNode != NULL) {
        if (currentNode->uId == userId) {
            strcpy(firstName, currentNode->fName);
            break;
        }
        currentNode = currentNode->next;
    }
}

void searchPhoneNumber(int userId, char *phoneNumber) {
    UD *currentNode = headUD;

    while (currentNode != NULL) {
        if (currentNode->uId == userId) {
            strcpy(phoneNumber, currentNode->pNumber);
            break;
        }
        currentNode = currentNode->next;
    }
}

void freeUd() {
    UD *current = headUD;
    UD *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    headUD = NULL; // Reset the head pointer after freeing all nodes
}

void freeCfs() {
    CFSS *current = headCFSS;
    CFSS *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    headCFSS = NULL; // Reset the head pointer after freeing all nodes
}
