#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void addarticle();

void viewarticle();

void editarticle();

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

        printf("\n\n\t\tMAIN MENU:");

        printf("\n\n\tADD article\t[1]");

        printf("\n\tVIEW article\t[2]");

        printf("\n\tEDIT article\t[3]");

        printf("\n\tEXIT\t\t[4]");

        printf("\n\n\tENTER YOUR CHOICE:");

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

            printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE ");

            getch();

            exit(0);

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

    scanf("%s", article.content);

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
        scanf("%s", article.content);
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