#include <stdio.h>
#include <conio.h>

#define MAX_LEN 100 // maximum length of a line

int main()
{
    char line[MAX_LEN]; // array to store the input line

    // Read multiple lines of input from the user until an empty line is entered
    fgets(line, MAX_LEN, stdin);

    printf("You entered: %s", line);
    getch();
    return 0;
}
