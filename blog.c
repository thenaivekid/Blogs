#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int main(){
    auth();
    int ch;
    char name[] = "none";
    char again;
    do{
        printf("\nEnter 1 to add article:\n");
        printf("Enter 2 to view article:\n");
        printf("Enter 3 to edit article:\n");
        printf("Enter 4 to view all articles:\n");
        printf("Enter 5 to view Bloggers:\n");
        printf("Enter 6 to read wiki from Wikipedia.com:\n");

        printf("\n\n\tENTER YOUR CHOICE:");
        fflush(stdin);
        scanf("%d", &ch);

        switch (ch){

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
            break;
        }
        printf("Do you want to continue? (y/n) ");
        scanf(" %c", &again);
        again = tolower(again);
    }
    while(again == 'y');
    return 0;
}

void addarticle(){
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

void viewarticle(char *name){
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
        printf("\nEdited: %s\n", article.edited);
        fclose(fpte);
    }
    else
    {
        printf("\nFile not found! \nTry to find it on the wikipedia here:\n");
        get_wiki();
    }
}

void editarticle(){
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
    char title[30];
    struct Blog blog;
    
    FILE *fp;
    fp = fopen("usersBlog.txt", "r");
    while (fread(&blog, sizeof(struct Blog), 1, fp) == 1) {
        printf("%s\n",blog.title);
    }
    fclose(fp);

    // view a blog
    
    printf("Enter the name of blog: ");
    getchar();
    scanf("%s",title);
    viewarticle(title);
    return;
}

void viewUser()
{    
    FILE *fp;
    fp = fopen("Users.txt", "rb");
    if(!fp){
        printf("Couldn't open the file!");
        return;
    }
    // count no of users
    int userCounter = 0;
    char buffer[2048];
    // Read the file and count the structs
    while (fread(&buffer, sizeof(struct User), 1, fp) == 1) {
        userCounter++;
    }
    rewind(fp);

    struct User *user;
    user = (struct User *) malloc(userCounter * sizeof(struct User));
    fread(user, sizeof(struct User), userCounter, fp);
    for (int i = 0; i < userCounter; i++)
    {
        printf("\n%s", user[i].name);
    }

    
    printf("\nChoose the blogger: ");
    char name[50];
    getchar();
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = 0;
    
    // to check if any user is found.
    int check = 0;
    for (int i = 0; i < userCounter; i++)
    {
        if (!strcmp(user[i].name, name))
        {
            printf("\n\t\t\t\t\t\t%s\n", user[i].name);
            printf("\n|Email:\t\t%s", user[i].email);
            printf("\n|Contact no.:\n%s", user[i].contacts);
            check = 1;
        }
    }
    if(check==0)
        printf("No match\n");
    fclose(fp);

    // show blogs by selected user
    FILE *fpBlog;
    fpBlog = fopen("usersBlog.txt", "r");
    if(!fpBlog){
        printf("Couldn't open the file!");
        return;
    }
    int blogCounter = 0;
    while (fread(&buffer, sizeof(struct Blog), 1, fpBlog) == 1) {
        blogCounter++;
    }
    rewind(fpBlog);
    struct Blog *blog;
    blog = (struct Blog *) malloc(blogCounter * sizeof(struct Blog));
    fread(blog, sizeof(struct Blog), blogCounter, fpBlog);

    for(int i= 0; i<blogCounter; i++){
        if (strcmp(blog[i].username,name)==0){
            printf("\n%d.%s\n",i,blog[i].title);
            printf("%s\n",blog[i].content);
            printf("Edited: %s\n",blog[i].edited);
        }
    }

    fclose(fpBlog);
    free(user);
    free(blog);
    return;
}

void get_wiki() {
    char command[1000];
    sprintf(command, "python3 -c \"from wiki import get_wiki; get_wiki()\"");
    system(command);
    return;
}