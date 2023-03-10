#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "authentication.h"

void addArticle();
void viewArticle();
void editArticle();
void viewAll();
void getWiki();
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
    // auth();
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
            addArticle();
            break;

        case 2:
            viewArticle(name);
            break;

        case 3:
            editArticle();
            break;

        case 4:
            viewAll();
            break;

        case 5:
            viewUser();
            break;

        case 6:
            getWiki();
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

void addArticle(){
    FILE *fp;
    char title[30],username[30],content[30];
    struct Blog article;

    printf("\n\tENTER TITLE: ");
    getchar();
    scanf("%s",title);
    printf("\n\tENTER USERNAME: ");
    getchar();
    scanf("%s",username);
    printf("\n\tENTER Content: ");
    getchar();
    fgets(content, 1024, stdin);


    strcpy(article.edited, "false");
    strcpy(article.title, title);
    strcpy(article.username, username);
    strcpy(article.content, content);

    // printf("%s\n",article.title);
    // printf("%s\n",article.username);
    // printf("%s\n",article.content);

// write the blog in a file with the name title.
    fp = fopen(title, "wb");
    if (fp ==NULL)
        printf("can't open file.");
    fwrite(&article, sizeof(struct Blog), 1, fp);
    if(fwrite==0){
        printf("couldn't write in the file.");
        fclose(fp);
        exit(1);
    }
    printf("\nYOUR article HAS BEEN ADDED...\n");
    fclose(fp);

    fp = fopen(title, "wb");
    if (fp ==NULL){
        printf("can't open file.");
        exit(1);
    }
    fwrite(&article, sizeof(struct Blog), 1, fp);
    if(fwrite==0){
        printf("couldn't write in the file.");
        fclose(fp);
        exit(1);
    }
    printf("\nYOUR article HAS BEEN ADDED in a file...\n");
    fclose(fp);

    // save the blog in userwiseBlog file 
    fp = fopen("userwiseBlog.dat", "ab+");
    if (fp ==NULL){
        printf("can't open file.");
        exit(1);
    }
    fwrite(&article, sizeof(struct Blog), 1, fp);
    if(fwrite==0){
        printf("couldn't write in the file.");
        fclose(fp);
        exit(1);
    }
    printf("\nYOUR article HAS BEEN ADDED to userwiseBlog...\n");
    fclose(fp);
}

void viewArticle(char *name){
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
        getWiki();
    }
}

void editArticle(){
    FILE *fpte;

    struct Blog article;
    char filename[30];
    fflush(stdin);
    printf("\nEnter the name of the file.\n");
    scanf("%s", filename);

    fpte = fopen(filename,"rb");
    if (fpte == NULL)
    {
        printf("can't open the file");
        fclose(fpte);
        exit(1);
    }

    fread(&article, sizeof(struct Blog), 1, fpte);
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
    printf("\nChanges saved  to blog file.");
    return;
}

void viewAll()
{
    char title[30];
    struct Blog blog;
    
    FILE *fp;
    fp = fopen("userwiseBlog.dat", "rb");
    while (fread(&blog,sizeof(struct Blog), 1, fp) == 1) {
        printf("%s\n",blog.title);
    }
    fclose(fp);

    // view a blog
    printf("Enter the name of blog: ");
    getchar();
    scanf("%s",title);
    viewArticle(title);
    return;
}

void viewUser()
{    
    FILE *fp;
    fp = fopen("Users.txt","rb");
    if(!fp){
        printf("Couldn't open the users file file!");
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
    char name[30];
    getchar();
    scanf("%s",name);
    
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
    if(check==0){
        printf("No match\n");
        fclose(fp); 
        return;
    }

    // show blogs by selected user
    fp = fopen("userwiseBlog.dat", "rb");
    if(!fp){
        printf("Couldn't open the userwiseBlog file!");
        return;
    }
    int blogCounter = 0;
    while (fread(&buffer, sizeof(struct Blog), 1, fp) == 1) {
        blogCounter++;
    }
    rewind(fp);
    struct Blog *blog;
    blog = (struct Blog *) malloc(blogCounter * sizeof(struct Blog));
    fread(blog, sizeof(struct Blog), blogCounter, fp);
    printf("\nBlogs\n");
    for(int i= 0; i<blogCounter; i++){
        if (strcmp(blog[i].username,name)==0){
            printf("\n%d.%s\n",i,blog[i].title);
            printf("%s\n",blog[i].content);
            printf("Edited: %s\n",blog[i].edited);
        }
    }

    fclose(fp);
    free(user);
    free(blog);
    return;
}

void getWiki() {
    char command[1000];
    sprintf(command, "python3 -c \"from wiki import getWiki; getWiki()\"");
    system(command);
    return;
}