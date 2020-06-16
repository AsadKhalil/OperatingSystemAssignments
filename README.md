# OperatingSystemAssignments

<h1>Assignment 0 – Revisiting File Handing</h1>

This is the introductory level assignment. This means it has low impact on your grade. You are however required to submit it.
Assignment Statement:
This assignment will be a revision to the concepts and implementations of file handling and that in C programming language. We shall see some must know and basic functions.
The basic functions are:
1)	Opening/Creating a file
2)	Closing a file
3)	Reading a file
4)	Writing in a file
In C language, we use a structure pointer of file type to declare a file.
FILE *fp;
The table below provides a list of functions you should know in order to perform the basic tasks listed above: 
FUNCTION	USAGE
fopen()	create a new file or open an existing file
fclose()	closes a file
fgetc()	reads a character from a file
fputc()	writes a character to a file
fputs()	writes a line of characters to a file
fgets()	Reads a line of characters from a file
fscanf()	reads a set of data from a file
fprintf()	writes a set of data to a file
getw()	reads a integer from a file
putw()	writes a integer to a file
fseek()	set the position to desire point
ftell()	returns current position of file 

1)	 *fp = FILE *fopen(const char *filename, const char *mode);
Following are the modes for fopen:

i.	r or rb
Open file for reading.
ii.	w or wb
Truncate to zero length or create file for writing.
iii.	a or ab
Append; open or create file for writing at end-of-file.
iv.	r+ or rb+ or r+b
Open file for update (reading and writing).
v.	w+ or wb+ or w+b
Truncate to zero length or create file for update.
vi.	a+ or ab+ or a+b
Append; open or create file for update, writing at end-of-file.

**Note: “b” is for binary files

2)	int fclose( FILE *fp);
3)	int fgetc(FILE *stream)  
4)	int fputc(int c, FILE *stream)  
5)	char* fgets(char *s, int n, FILE *stream)  
6)	int fputs(const char *s, FILE *stream)  
7)	int fscanf(FILE *stream, const char *format [, argument, ...])  
8)	int fprintf(FILE *stream, const char *format [, argument, ...])
9)	int getw(FILE *fp);
10)	int putw(int number, FILE *fp);
11)	int fseek(FILE *stream, long int offset, int whence)  
12)	long ftell(FILE *stream)


Your Tasks:
Following tasks are to be done:
1)	Write a program to read a file and count the number of digits in it. The file may contain an alphanumeric string.
2)	Write a program to manage record of student registration on file. Enter your details and the details of two of your classmates. Roll no, Name and Email should be saved as student details. Example Record:
Name:
Roll No.
Email: 
	Take input via command line argument or user input.
Your program should do the following:
a.	Allow Adding students
b.	Read student record from file. (Program must take input from user to read a record. E.g. “0” to read your record, “1” and “2” to read record of fellow student.)
c.	Delete student record in file. (Program must take input from user to delete a record. E.g. “0” to delete your record, “1” and “2” to delete record of fellow student.)
3)	Write a program that reverses all the characters of words that are not vowels in a given file.
NOTE: Task 1 and 3 should accept a command line argument which will indicate which file to use for answer validation. For example, the input to task 1 can be something like this:
>  ./program.out a
OR
>  ./program.out b

<h1>Assignment 1</h1>

<h3>Introduction</h3>

The goal of the first assignment is to write our own, very simple, shell. The shell should print a command prompt and allow the user to enter a command. After entering this command, the shell should properly execute the command, this includes supplying the provided arguments to the program. The user can exit the shell using the exit command. The shell should also have a functioning cd command to change the current working directory and the shell should show the current working directory in the prompt.
A simple version of the ls command must be included. Using these simple system commands, bigger commands can be created where the output of one command is sent to another. This is for instance done using the pipe character (|).
Through redirection, using the > symbol, the output of a program can be redirected to a file that is stored on disk. As the final part of this assignment you will implement (simplified) support for handling pipes and redirection, so that your shell is capable of executing commands such as cat Makefile | grep gcc, sort Makefile > sorted.txt and cat words.txt | sort > sortedwords.txt.

<h3>  Specification</h3>
The assignment is to program a shell program that conforms to the specification given in this section. The shell must be written in plain C. This is to prepare for the actual kernel coding in the next assignment, in which only plain C can be used. Make sure to use a C and not a C++ compiler to warn you for the use of C++ constructs, because points will be deducted when C++ constructs are used in the code. The shell should have the following features:
1. Print a command prompt that also displays the current working directory.
2. Allow the user to enter commands and execute these commands.
3. The entered command string must be tokenized into an array of strings by removing the space delimiters. Also delimiters consisting of more than one space must be handled correctly.
4. Implement exit (to exit the shell) and cd (to change the current working directory) as built-in commands. The cd should display errors if necessary.
5. Ability to find program to be launched in the file system using a hard-coded array of standard locations in case the name of the executable is not preceded by an absolute or relative path. You must implement this yourself, do not use execlp or execvp.
6.Display an appropriate error if a requested command cannot be found or is not executable.
7. Execute commands and correctly pass the provided arguments to this command.
8. Execute commands that contain a pipe character by starting two new processes that are interconnected with a pipe. Your shell should be able to handle data streams of arbitrary length.
a. Note 1: your shell only has to be capable of running commands that contain a single pipe character. Check how many pipe characters a command contains and simply display an error if more than one pipe character is found.
  b. Note 2: to simplify implementation, you only have to deal with the case that the pipe character is separated by spaces, so the tokenizer you have to implement already creates a separate token for the pipe character. For instance, a command of the form cat Makefile|wc -l does not have to be handled correctly by your program.
9. Execute commands that contain a redirection character by redirecting the output of the command to the given filename. If the file already exists, it should be overwritten. The redirection character will only be specified once and only has to function for stdout (file descriptor 1). Example: sort words.txt > sorted.txt.
10. Execute commands that contain both a single pipe character and a single redirection character. Example: cat words.txt | sort > sorted.txt.
  a. Note: you may assume that the redirection character and associated filename will always be located at the end of the command and that the redirection character is separated with spaces. So, a redirection character may not occur before the pipe character.
Guide to library functions
You will have to use library functions to accomplish the various tasks. Some of these library functions are wrappers around actual system calls (POSIX API), which are traps to the operating system kernel (e.g. fork and execv).
Reading and parsing user input. There are several ways to obtain input from the user, we suggest to use fgets. The command string entered by the user will have to be split (or tokenized) into an argument vector using the space character as delimiter. You can do this tokenization manually, or use a provided string manipulation function such as strsep. Make sure to also properly deal with delimiters consisting of multiple spaces.
Executing a program. To start a new process and execute a program the fork and execv should be all you need. In the parent process you will need to use the wait system call. The first item in the argument vector indicates the program to run. If this item does not contain a slash, it is not a relative or absolute path and we must find out where this program is located in the file system. To do so, concatenate the name of the program to each of the paths in the hard-coded path array and use, for example, the stat call to test whether the file exists.
Creating a pipe. To create a pipe you have to use the pipe system call. You have to pass an array of two integers as an argument, which will be filled with the file descriptors of the input and output end of the pipe. To reconnect standard input and output to the pipe, you will also need the close and dup system calls. Also useful are the defines STDIN_FILENO and STDOUT_FILENO that represent the file descriptors for stdin and stdout respectively.

<h3>Guide to library functions</h3>
You will have to use library functions to accomplish the various tasks. Some of these library functions are wrappers around actual system calls (POSIX API), which are traps to the operating system kernel (e.g. fork and execv).
Reading and parsing user input. There are several ways to obtain input from the user, we suggest to use fgets. The command string entered by the user will have to be split (or tokenized) into an argument vector using the space character as delimiter. You can do this tokenization manually, or use a provided string manipulation function such as strsep. Make sure to also properly deal with delimiters consisting of multiple spaces.
Executing a program. To start a new process and execute a program the fork and execv should be all you need. In the parent process you will need to use the wait system call. The first item in the argument vector indicates the program to run. If this item does not contain a slash, it is not a relative or absolute path and we must find out where this program is located in the file system. To do so, concatenate the name of the program to each of the paths in the hard-coded path array and use, for example, the stat call to test whether the file exists.
Creating a pipe. To create a pipe you have to use the pipe system call. You have to pass an array of two integers as an argument, which will be filled with the file descriptors of the input and output end of the pipe. To reconnect standard input and output to the pipe, you will also need the close and dup system calls. Also useful are the defines STDIN_FILENO and STDOUT_FILENO that represent the file descriptors for stdin and stdout respectively.

<h1>  Assignment-2</h1>
<h3>Assignment Statement:</h3>
Now that you have understood pipes in detail, lets answer an interesting question with the help of this assignment. Suppose you have a parent having two children as shown in figure 1. The parent can write to the pipe and the children can read the data from the pipe. The question is, when the parent sends data on to the pipe, will both the children read that data or only one of the two? If only one, what will the other user do in that case?
To answer this question, you will have to develop a C program in which a parent will be able to communicate with its children as shown in figure 2 below.
Show that the parent sends message over the pipe and both the children are reading that data. Print a message in both children indicating whether they received data or not. Whatever is the behavior of the program, write the behavior in few lines in a supporting document


<h1>  Assignment-3</h1>
<h3>Assignment Statement:</h3>
<h2>Task 1: COVID-19 Management System</h2>
Help the world in crisis by developing a Coronavirus (COVID-19) management system.
You are required to manage the number of coronavirus patients via threads and semaphores. Suppose N number of potential Corona patients enter the hospital. You will have to write a program that initializes N threads simultaneously where each thread increments a shared variable potentialCPatients. After tests are being carried out for each potential patient, a patient may either be infected or not infected by coronoavirus in a random fashion. If the patient is infected, a semaphore called coronaPatient will be signaled/incremented. Whereas if the patient is NOT infected, a semaphore called fluPatient will be signaled/incremented. In either case, the shared variable called potentialCpatient variable will be decremented. You are not concerned with the recovery of the flu patients but only with the coronavirus patients. Eventually, each corona patient has to get better. For this purpose, each corona patient will go through tests and wait will be called for the coronaPatient only after two consecutive tests return false.
NOTE: Create necessary functions to enhance code readability. Also, N must be taken as user input.
<h2>Task 2: Process Synchronization and Order</h2>
Four processes are involved in printing files characters (pictured below). Using semaphore(s), order the execution of these processes such that first 10 characters are printed from each file 1 and 2. All four processes are spawned by the parent process at the same time. However, the execution of process D waits for the execution of process C. Whereas the execution of process C waits for the execution of process A and B. Also, remember that process A and B can both write on the same Buffer-1. Therefore, data must NOT be overwritten on Buffer-1 and synchronization must be ensured on Buffer-1 between process A and B.


<h1>  Assignment-4</h1>
<h3>Assignment Statement:</h3>

You have to implement your own file systems. The first time your utility will runs, it will ask user following arguments
• Block size of the virtual hard drive you will create
• Name of the file which will be treated as the new virtual hard drive
• Path of a directory which you will import as a root file system into your virtual hard drive
In the subsequent runs, if the virtual hard drive should already be present in the same directory, your utility should not ask any of the above things.
In the virtual hard drive there will be two portions
• Volume Control block which will store the directory tree along with the FCBs. It will also have the FAT table to keep track of the data and free space
• All other blocks will be treated as Data blocks. Number of data blocks should be 1000 regardless of the size of the block.
You need to implement following five commands
• ls lists the contents of a directory
• rm removes a directory or a path
• mkdir creates a directory
• cd changes the present working directory
• import imports a file from the host system to the path specified in the arguments.
Directory tree and FCBs can be implemented using JSON (you may have to search on how this can be done). In the JSON there will be three types of keys:
• Keys with no value: they will represent empty directories
• Keys with dictionary value: they will represent directories containing one or more directories or files
• Keys with integer value: they will represent a file control block, integer being the starting data block number.
Submission: The submission should contain only following things. If there is one missing then the assignment will be given 0 marks. Additional things will also be penalized.
1. Assign-4.cpp the code of the assignment
2. Makefile which makes executing make command in the respective directory compile the code into an executable.
After executing make an executable should be created named assign-4.o. Executing that executable should generate all the respective output files.

