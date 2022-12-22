#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 10
#define MAX_LENGTH 50

int main()
{
    char strings[MAX_STRINGS][MAX_LENGTH];
    int i;

    /* add some strings to the array */
    for (i = 0; i < MAX_STRINGS; i++)
    {
        char str[MAX_LENGTH];
        printf("Enter a string: ");
        scanf("%s", str);
        snprintf(strings[i], MAX_LENGTH, "%s", str);
    }

    /* print the strings in the array */
    for (i = 0; i < MAX_STRINGS; i++)
    {
        printf("%s\n", strings[i]);
    }

    return 0;
}
