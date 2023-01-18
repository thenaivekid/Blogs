#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MIN_PASSWORD_LENGTH 8

struct User
{
	char email[50];
	char password[50];
	char name[50];
	char contacts[200];
};

bool is_valid_password(char password[]) {
	// Check password length
	if (strlen(password) < MIN_PASSWORD_LENGTH) {
		return false;
	}

	// Check for at least one digit
	bool has_digit = false;
	for (int i = 0; i < strlen(password); i++) {
		if (isdigit(password[i])) {
		has_digit = true;
		break;
		}
	}
	if (!has_digit) {
		return false;
	}

	// Check for at least one uppercase letter
	bool has_uppercase = false;
	for (int i = 0; i < strlen(password); i++) {
		if (isupper(password[i])) {
		has_uppercase = true;
		break;
		}
	}
	if (!has_uppercase) {
		return false;
	}

	// Password is valid
	return true;
}


int signup() {
    struct User user;
    char password1[50],password2[50];

	printf("\nEnter your name: ");
	scanf("%s", user.name);

	printf("Enter your email: ");
	scanf("%s", user.email);
	printf("Enter your contacts (separated by commas): ");
	scanf("%s", user.contacts);
	getchar();
	printf("Enter your password: ");
	scanf("%s", password1);
	if(!is_valid_password(password1))
	{
		printf("\nPassword must contain at least one uppercase letter, at least one number and at least 8 characters.\n");
		return 0;
	}

	printf("\nEnter your password: ");
	scanf("%s", password2);

	if(strcmp(password1,password2)!=0)
	{
		printf("\nPassword didn't match!\n");
		return 0;
	}

	strcpy(user.password,password1);

	FILE *fp;
	fp = fopen("Users.txt", "ab+");
	if (fp == NULL)
		{
		perror("\nError opening file");
		return 0;
	}


    fwrite(&user, sizeof(struct User), 1, fp);
    if (fwrite != 0)
    {
        printf("\n\nUser resgistration success, \nLogged in as %s\n", user.name);
        fclose(fp);
        return 1;
    }
    else
        printf("\n\nSorry! Something went wrong :(");

    fclose(fp);

    return 0;
}


int login()
{
    FILE *fp;
    char name[50], password[50];
    int userFound;
    struct User user[10];

    printf("\nEnter your username:\t");
    scanf("%s",name);

    printf("\nEnter your password:\t");
    scanf("%s",password);

    fp = fopen("Users.txt", "rb");
    if (fp == NULL) {
        perror("\nError opening file");
        return 0;
    }


    for (int i = 0; i < 10; i++)
    {
        fread(&user[i], sizeof(user[i]), 1, fp);
    }

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(user[i].name, name)==0)
        {
            if (strcmp(user[i].password, password)==0)
            {
                system("cls");
                printf("\n\t\t\t\t\t\tWelcome %s\n", user[i].name);
                printf("\n|Email:\t\t%s", user[i].email);
                printf("\n|Contacts:\t%s\n", user[i].contacts);
                fclose(fp);
                return 1;
            }
            else
            {
                printf("\n\nInvalid Password!");
                fclose(fp);
                return 0;
            }
        }
    }

    printf("\n\nUser is not registered!\n");
    printf("\nSign in first\n");
    fclose(fp);
    return 0;
}


void auth() 
{
    int opt;
    system("cls");
    printf("\n\t\t\t\t----------Welcome to authentication system----------");
    printf("\nPlease choose your operation");
    printf("\n1.Signup");
    printf("\n2.Login");
    printf("\n3.Exit");

    printf("\n\nYour choice:\t");
    scanf("%d", &opt);
    fgetc(stdin);

    switch (opt)
    {
    case 1:
        opt = signup();
        if(opt!=1)
            auth();
        return;
    case 2:
        opt = login();
        if(opt!=1)
            auth();
        return;
        
    case 3:
        printf("\t\t\tBye Bye :)");
        exit(1);
    }
    
}