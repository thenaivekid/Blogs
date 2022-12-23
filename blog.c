#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#include <dos.h>

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void addarticle();

void viewarticle();

void editarticle();

void viewAll();

struct blog

{
    char title[30];
    char username[50];
    char content[1024];
};

int main()

{

    int ch;

    while (1)

    {

        system("cls");
        gotoxy(30, 1);
        printf("\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Blogs \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3");
        gotoxy(31, 4);
        printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 1.Add New");
        gotoxy(31, 7);
        printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 2.Search blog");
        gotoxy(31, 10);
        printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 3.Edit blog");
        gotoxy(31, 13);
        printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 4.All blogs");
        gotoxy(31, 16);
        printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 5.Delete");

        printf("\n\n\tENTER YOUR CHOICE:");
        fflush(stdin);
        scanf("%d", &ch);

        switch (ch)

        {

        case 1:

            addarticle();

            break;

        case 2:

            viewarticle();

            break;

        case 3:

            editarticle();

            break;

        case 4:
            viewAll();
            getch();

        default:

            printf("\nYOU ENTERED WRONG CHOICE..");

            printf("\nPRESS ANY KEY TO TRY AGAIN");

            getch();

            break;
        }

        system("cls");
    }

    return 0;
}

void addarticle()

{

    system("cls");

    FILE *fp;

    struct blog article;

    fflush(stdin);

    printf("\n\tENTER TITLE: ");

    scanf("%s", article.title);

    fflush(stdin);

    printf("\n\tENTER USERNAME: ");

    scanf("%s", article.username);

    fflush(stdin);

    printf("\n\tENTER Content: ");

    fgets(article.content, 1024, stdin);
    fp = fopen(article.title, "wb+");

    fwrite(&article, sizeof(article), 1, fp);

    printf("\nYOUR article HAS BEEN ADDED...\n");

    fclose(fp);

    printf("\n\n\tPRESS ANY KEY TO EXIT...");

    getch();
}

void viewarticle()

{

    FILE *fpte;

    system("cls");

    struct blog article;

    char filename[30];
    fflush(stdin);
    printf("Enter the name of the file.\n");
    scanf("%s", filename);

    fpte = fopen(filename, "rb");
    if (fpte != NULL)
    {

        system("cls");

        fread(&article, sizeof(article), 1, fpte);

        printf("\nTITLE: %s", article.title);

        printf("\nBy: %s", article.username);

        printf("\n%s", article.content);
        fclose(fpte);
        getch();
    }
    else
    {
        printf("\nFile not found!\n");
        getch();
    }
}

void editarticle()

{

    system("cls");

    FILE *fpte;

    struct blog article;
    char filename[30];
    fflush(stdin);
    printf("\nEnter the name of the file.\n");
    scanf("%s", filename);

    fpte = fopen(filename, "rb");
    if (fpte != NULL)
    {
        system("cls");

        fread(&article, sizeof(article), 1, fpte);

        printf("\nTITLE: %s", article.title);

        printf("\nBy: %s", article.username);

        printf("\n%s", article.content);

        fclose(fpte);
        printf("\nEnter new content: \n");
        fflush(stdin);
        fgets(article.content, 1024, stdin);
        fpte = fopen(filename, "wb");
        fwrite(&article, sizeof(article), 1, fpte);
        fclose(fpte);
        printf("\nChanges saved.");
        getch();
    }
    else
    {
        printf("File not found!");
        getch();
    }
}

void viewAll()
{
    DIR *dir;
    struct dirent *ent;
    char strings[20][50];
    int i = 0;

    /* add some strings to the array */

    if ((dir = opendir(".")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            /* check if the file has a .c extension */
            if (strstr(ent->d_name, ".exe") == NULL)
            {
                snprintf(strings[i], 50, "%s", ent->d_name);
                i++;
            }
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        printf("Couldn't open");
        getch();
    }

    char filename[50];
    int choice = 1;
    while (choice == 1)
    { /* print the strings in the array */
        for (i = 0; i < 20; i++)
        {
            printf("%s\n", strings[i]);
        }
        struct blog article;
        fflush(stdin);
        printf("\nEnter the name of the blog you want to read: ");

        scanf("%s", filename);
        FILE *fp;
        fp = fopen(filename, "rb");
        if (fp != NULL)
        {

            system("cls");

            fread(&article, sizeof(article), 1, fp);

            printf("\nTITLE: %s", article.title);

            printf("\nBy: %s", article.username);

            printf("\n%s", article.content);
            fclose(fp);
        }
        else
        {
            printf("\nFile not found!\n");
        }
        printf("\n\n\n\n\nEnter 1 for another blog \nEnter any other integer for main menu: ");
        scanf("%d", &choice);
    }
}