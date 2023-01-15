#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "authentication.h"


void addarticle();

void viewarticle();

void editarticle();

void viewAll();

void get_wiki();

void viewUser();

struct User
{
    char email[50];
    char password[50];
    char name[50];
    char contacts[200];
};

struct Blog

{
    char title[30];
    char username[50];
    char content[1024];
    char edited[8];

};

int main()

{
    // auth();
    int ch;
    char name[] = "none";

    printf("\nEnter 1 to add article:\n");
    printf("Enter 2 to view article:\n");
    printf("Enter 3 to edit article:\n");
    printf("Enter 4 to view all articles:\n");
    printf("Enter 5 to view Bloggers:\n");
    printf("Enter 6 to read wiki from Wikipedia.com:\n");

    printf("\n\n\tENTER YOUR CHOICE:");
    fflush(stdin);
    scanf("%d", &ch);

    switch (ch)

    {

    case 1:

        addarticle();

        break;

    case 2:
        
        viewarticle(name);

        break;

    case 3:

        editarticle();

        break;

    case 4:
        viewAll();
        break;

    case 5:
        viewUser();
        break;

    case 6:
        get_wiki();
        break;

    default:

        printf("\nYOU ENTERED WRONG CHOICE..");

        printf("\nPRESS ANY KEY TO TRY AGAIN");


        break;
    }



    return 0;
}
void addarticle()
{


    FILE *fp, *fptr;

    struct Blog article;

    fflush(stdin);

    printf("\n\tENTER TITLE: ");

    scanf("%s", article.title);

    fflush(stdin);

    printf("\n\tENTER USERNAME: ");

    scanf("%s", article.username);

    fflush(stdin);

    printf("\n\tENTER Content: ");
    getchar();
    fgets(article.content, 1024, stdin);
    strcpy(article.edited, "false");
    fp = fopen(article.title, "wb+");
    fptr = fopen("usersBlog.txt", "ab+");
    fwrite(&article, sizeof(article), 1, fp);
    fwrite(&article, sizeof(article), 1, fptr);
    printf("\nYOUR article HAS BEEN ADDED...\n");

    fclose(fp);
    fclose(fptr);

}


void viewarticle(char *name)
{

    FILE *fpte;
    char filename[30];
    struct Blog article;
    if (strcmp(name,"none")==0){
        printf("Enter the name of the file.\n");
        scanf("%s", filename);
    }
    else
        strcpy(filename,name);

    fpte = fopen(filename, "rb");
    if (fpte != NULL)
    {


        fread(&article, sizeof(article), 1, fpte);

        printf("\nTITLE: %s", article.title);

        printf("\nBy: %s", article.username);

        printf("\n%s", article.content);
        printf("\nEdited: %s", article.edited);


        fclose(fpte);
    }
    else
    {
        printf("\nFile not found! \nTry to find it on the wikipedia here:\n");
        get_wiki();
    }
}

void editarticle()

{

    FILE *fpte;

    struct Blog article;
    char filename[30];
    fflush(stdin);
    printf("\nEnter the name of the file.\n");
    scanf("%s", filename);

    fpte = fopen(filename, "rb");
    if (fpte != NULL)
    {

        fread(&article, sizeof(article), 1, fpte);

        printf("\nTITLE: %s", article.title);

        printf("\nBy: %s", article.username);

        printf("\n%s", article.content);

        fclose(fpte);
        printf("\nEnter new content: \n");
        getchar();
        fgets(article.content, 1024, stdin);
        strcpy(article.edited,"true");

        fpte = fopen(filename, "wb");
        fwrite(&article, sizeof(article), 1, fpte);
        fclose(fpte);
        printf("\nChanges saved.");
    }
    else
    {
        printf("File not found!");
    }
}

void viewAll()
{
    int i = 0;
    char titles[20];
    struct Blog blog;
    
    FILE *fp;
    fp = fopen("usersBlog.txt", "r");
     while (fread(&blog, sizeof(struct Blog), 1, fp) == 1) {
        printf("%s\n",blog.title);
    }
    fclose(fp);
    return;
}

void viewUser()
{
    struct User user[10];
    struct Blog blog;
    FILE *fp, *fptr;
    fp = fopen("Users.txt", "r");
    for (int i = 0; i < 10; i++)
    {
        fread(&user[i], sizeof(user[i]), 1, fp);
    }
    for (int i = 0; i < 10; i++)
    {
        printf("\n%s", user[i].name);
    }
    printf("Choose the blogger: ");
    char name[50];
    getchar();
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = 0;
    // to check if any user is found.
    
    int check = 0;

    for (int i = 0; i < 10; i++)
    {
        if (!strcmp(user[i].name, name))
        {
            printf("\n\t\t\t\t\t\t%s\n", user[i].name);
            printf("\n|Email:\t\t%s", user[i].email);
            printf("\n|Contact no.:\t%s", user[i].contacts);
            printf("\n\t\t\tBlogs\n\n");
            fptr = fopen("usersBlog.txt", "r");
            while (fread(&blog, sizeof(blog), 1, fptr))
            {
                if (!strcmp(blog.username, user[i].name))
                {
                    printf("\n\n\nTitle:%s\n\n", blog.title);
                    printf("%s\n", blog.content);
                    printf("Edited: %s\n", blog.edited);
                    
                }
            }
            fclose(fptr);
            check = 1;
            break;
        }
    }
    fclose(fp);
    if (check == 0)
    {
        printf("\n No user found.\n");
    }
}

void get_wiki() {
    char command[1000];
    sprintf(command, "python3 -c \"from wiki import get_wiki; get_wiki()\"");
    system(command);
}