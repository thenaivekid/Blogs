# Blog

### Introduction
Wiki is very popular way of sharing knowledge that we have to others who need it and to gain knowledge from experts. People with common interest can meet and colaborate and come of with a better idea for everybody else. This CLI applications makes it possible.

This is app written in C program that does the following:
- Allows user to create new user account or log in.
- Write a blog about something.
- Edit the blog.
- View the blogs by other users as well as their own.
- View the contact details of the fellow bloggers so that they can connect and colab.

`#include <stdio.h>`,
`#include <stdlib.h>`,
`#include <conio.h>`,
`#include <string.h>`,
`#include <dirent.h>`,
`#include <windows.h>`,
`#include <dos.h>` are the only header files used in the program.



## `authhentication.c`
`authentication` is a simple authentication system for a command line program. The function presents the user with a menu of options: sign up, log in, or exit. If the user selects the sign up option, the signup() function is called. If the user selects the log in option, the login() function is called. If the user selects the exit option, the program terminates. If the user enters an invalid choice, the menu is displayed again.


`struct` called user that has five fields: fullName, email, password, username, and phone. Each field is a character array with a length of 50.

`takeInput` takes string input and adds 0 at the end of array.

`takepassword` is used to prompt the user to enter a password and store it in the character array pwd. It has the following behavior:

- It prompts the user to enter a password by printing a message to the console.
- As the user types in the password, each character is stored in the pwd array and displayed as an asterisk (*) on the screen.
- If the user presses the backspace key (BCKSPC), the last character in the pwd array is removed and the asterisk on the screen is also removed.
- If the user presses the enter key (ENTER) or the tab key (TAB), the password entry is completed and the function exits.
- If the password is less than 8 characters long, a message is displayed telling the user that the password must be at least 8 characters long and the user is prompted to enter the password again. This is accomplished using the goto statement, which jumps to the NOT_ENOUGH label and continues execution from there.

The function, `signup`, is used to allow a user to create a new account by signing up for a service. It has the following behavior:

- It prompts the user to enter their full name, username, email, and phone number, and stores these values in a user struct.
- It prompts the user to enter a password and stores it in the password field of the user struct. It then prompts the user to confirm the password and stores it in the password2 array.
- If the two passwords match, the function opens the Users.txt file in append mode and writes the user struct to the file using the fwrite function.
- If the write is successful, a message is displayed indicating that the user registration was successful and the user is logged in. The username is also copied to the returnValue array. If the write was unsuccessful, an error message is displayed.
- If the two passwords do not match, a message is displayed indicating that the passwords did not match and the user is prompted to enter the password again. This is accomplished using the goto statement, which jumps to the AGAIN label and continues execution from there.

The function, `signup`, is used to allow a user to create a new account by signing up for a service. It has the following behavior:

- It prompts the user to enter their full name, username, email, and phone number, and stores these values in a user struct.
- It prompts the user to enter a password and stores it in the password field of the user struct. It then prompts the user to confirm the password and stores it in the password2 array.
- If the two passwords match, the function opens the Users.txt file in append mode and writes the user struct to the file using the fwrite function.
- If the write is successful, a message is displayed indicating that the user registration was successful and the user is logged in. The username is also copied to the returnValue array. If the write was unsuccessful, an error message is displayed.
- If the two passwords do not match, a message is displayed indicating that the passwords did not match and the user is prompted to enter the password again. This is accomplished using the goto statement, which jumps to the AGAIN label and continues execution from there.

## `authentication.h`
This file contains the function `authentication` that is in the `authentication.c`.

## `blog.c`

The `blog` struct has three fields: `title`, `username`, and `content`. title is an array of characters (a string) with a maximum length of 30 characters. username is an array of characters with a maximum length of 50 characters. content is an array of characters with a maximum length of 1024 characters.

`main() ` is function for a command line program that allows the user to perform various operations on a collection of blog posts. The first thing the function does is call the authentication() function to allow the user to log in. The returned value is stored in a variable called `username`.

After the user has logged in, the program enters a loop that displays a menu of options to the user and waits for the user to choose one. The menu options are:

- Add a new blog post
- Search for a blog post
- Edit a blog post
- View all blog posts
- Connect with other bloggers
The user's choice is stored in the `ch` variable, and a `switch` statement is used to decide which action to take based on the user's choice. If the user selects option 1, the `addarticle()` function is called. If the user selects option 2, the `viewarticle()` function is called. If the user selects option 3, the `editarticle()` function is called. If the user selects option 4, the `viewAll()` function is called. If the user selects option 5, the `viewUser() `function is called. If the user enters an invalid choice, a message is displayed and the program returns to the menu.

`addarticle` function allows the user to add a new blog post to the program's collection of blog posts. It does this by asking the user to enter the title, username, and content of the new blog post, and then saving this information to a file.
The function starts by clearing the screen using the system("cls") function. It then declares a variable fp of type FILE*, which will be used to access the file where the blog post will be saved. It also declares a variable article of type struct blog and initializes its fields by asking the user to enter the title, username, and content of the new blog post.
Next, the function opens the file specified by the title field of the article struct in write-binary mode ("wb+"). This means that if the file doesn't exist, it will be created, and if it does exist, it will be overwritten. The function then writes the article struct to the file using the fwrite() function, which writes binary data to a file.
After the article struct has been written to the file, the function closes the file using the fclose() function and displays a message to the user indicating that the blog post has been added. Finally, the function waits for the user to press a key before exiting.

`viewarticle` function allows the user to view a specific blog post from the program's collection of blog posts. It does this by asking the user to enter the name of the file that contains the blog post, and then reading the file and displaying the contents to the user.
The function starts by clearing the screen using the system("cls") function. It then declares a variable fpte of type FILE*, which will be used to access the file where the blog post is stored. It also declares a variable article of type struct blog and a character array called filename that will be used to store the name of the file.
Next, the function asks the user to enter the name of the file and reads the user's input into the filename array using the scanf() function. The function then opens the file specified by the filename array in read-binary mode ("rb"). If the file can be opened successfully, the function reads the article struct from the file using the fread() function, which reads binary data from a file. The function then displays the contents of the article struct to the user, and closes the file using the fclose() function. If the file cannot be opened, the function displays a message to the user indicating that the file was not found. Finally, the function waits for the user to press a key before exiting.

`editarticle` function allows the user to edit a specific blog post from the program's collection of blog posts. It does this by asking the user to enter the name of the file that contains the blog post, reading the file and displaying the contents to the user, asking the user to enter new content for the blog post, and then overwriting the file with the new content.
The function starts by clearing the screen using the system("cls") function. It then declares a variable fpte of type FILE*, which will be used to access the file where the blog post is stored. It also declares a variable article of type struct blog and a character array called filename that will be used to store the name of the file.
Next, the function asks the user to enter the name of the file and reads the user's input into the filename array using the scanf() function. The function then opens the file specified by the filename array in read-binary mode ("rb"). If the file can be opened successfully, the function reads the article struct from the file using the fread() function, displays the contents of the article struct to the user, and closes the file using the fclose() function.
Next, the function asks the user to enter new content for the blog post and reads the user's input into the content field of the article struct using the fgets() function. The function then reopens the file in write-binary mode ("wb") and writes the updated article struct to the file using the fwrite() function. The function then closes the file and displays a message to the user indicating that the changes have been saved. If the file cannot be opened, the function displays a message to the user indicating that the file was not found. Finally, the function waits for the user to press a key before exiting.

`viewall` function allows the user to view all of the blog posts that are available in the program's collection of blog posts. It does this by opening the current directory (using the opendir() function) and reading the names of all of the files in the directory (using the readdir() function). It then stores the names of the files in an array of strings called strings, and displays the names of the files to the user.
The function starts by declaring a variable dir of type DIR* and a variable ent of type struct dirent*. It then initializes an array of strings called strings and a variable i to zero.
Next, the function opens the current directory using the opendir() function and assigns the resulting directory stream to the dir variable. If the directory was opened successfully, the function enters a loop that reads the names of all of the files in the directory using the readdir() function. For each file, the function checks if the file has a .exe extension (using the strstr() function) and, if it does not, stores the file name in the strings array using the snprintf() function and increments the value of i. When all of the files in the directory have been processed, the function closes the directory stream using the closedir() function. If the directory could not be opened, the function displays an error message to the user and waits for the user to press a key.
After all of the file names have been stored in the strings array, the function enters a loop that allows the user to view the contents of any of the files. It does this by asking the user to enter the name of the file they want to view and then opening the file in read-binary mode (using the `fopen`).

`viewuser` function allows the user to view the details of a specific user in the program's collection of users. It does this by reading a list of users from a file called Users.txt and storing the user details in an array of struct user called usr. It then asks the user to enter the username of the user they want to view, searches the usr array for a user with a matching username, and displays the details of the user if a match is found.
The function starts by declaring a variable fp of type FILE* and an array of struct user called usr. It then opens the Users.txt file in read mode (using the fopen() function) and assigns the resulting file stream to the fp variable. It then reads the usr array from the file using the fread() function and closes the file using the fclose() function.
Next, the function displays the username of each user in the usr array to the user and asks the user to enter the name of the user they want to view. It reads the user's input into a character array called name using the fgets() function and removes the trailing newline character from the name array using the strlen() function.
The function then enters a loop that searches the usr array for a user with a matching username. If a matching user is found, the function displays the details of the user and sets a variable check to 1. If no matching user is found, the function continues searching until the end of the usr array is reached.
Finally, the function checks the value of check. If check is 0, it means that no matching user was found and the function displays a message to the user indicating this. If check is 1, it means that a matching user was found and the function does nothing else.