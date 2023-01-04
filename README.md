# Blog
## Written entirely in C programmng language.
### Introduction
Wiki is very popular way of sharing knowledge that we have to others who need it and to gain knowledge from experts. People with common interest can meet and colaborate and come of with a better idea for everybody else. This CLI applications makes it possible.

This is app written in C program that does the following:
- Allows user to create new user account or log in.
- Write a blog about something.
- Edit the blog.
- View the blogs by other users as well as their own.
- View the contact details of the fellow bloggers and their blogs in profile view.
- In case the required blog is not locally available, user can read wiki from wikipedia.com right in the command line.

### To build  the executable file from codes all you need to do is run the following command in the folder containing source codes: 
```
gcc auth.c blog.c -o run
```

### To run the program
```
./run
```

`blog.c` first authenticates the user using `authentication.c` included in `authentication.h`. Then asks the user to choose what action to take. According to the choice of the user, program takes the user to requested places. `addarticle` lets user to add new blog to the platform. `viewarticle` lets user to view the article by searching while `viewall` lets user choose the article by displaying all the files in the current directory using `dirent.h`. `editarticle` lets user edit existing article by reading old file and saving new file with edited content. `viewUser` lets user to view contact details of the queried blogger if one exists.`get_wiki` lets user search the wikipedia.com and read the wiki right from the command line.