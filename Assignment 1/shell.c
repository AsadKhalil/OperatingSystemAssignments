#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

void initializeShell()
{
    char* username = getenv("USER");    //return the current User of OS
    printf("Initializing Shell......"); 
    printf("\nUSER is: @%s", username); 
    printf("\n"); 
    sleep(1); 
}
void printCurrentDirectory() 
{ 
    char cwd[1024];                    //return current working directory
    getcwd(cwd, sizeof(cwd)); 
    printf("\nCurrent Directory: %s", cwd); 
}
int Input(char* str) 
{ 
    char* buffer; 
  
    buffer = readline(":~$  "); 
    if (strlen(buffer) != 0) 
    { 
     	// add_history(buffer);   //store every line in the history
        strcpy(str, buffer); 
        return 0; 
    } 
    else 
    { 
        return 1; 
    } 
} 
// function for finding pipe 
int parsePipe(char* str, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < 2; i++) 
    { 
        strpiped[i] = strsep(&str, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else
    { 
        return 1; 
    } 
} 

// Function to execute builtin commands 
int ownCmdHandler(char** parsed) 
{ 
    int NoOfOwnCmds = 3, i, switchCommand = 0; 
    char* ListOfOwnCmds[NoOfOwnCmds]; 
    char* username; 
  
    ListOfOwnCmds[0] = "exit"; 
    ListOfOwnCmds[1] = "cd"; 
    ListOfOwnCmds[2] = "help"; 

  
    for (i = 0; i < NoOfOwnCmds; i++) { 
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) { 
            switchCommand = i + 1; 
            break; 
        } 
    } 
  
    switch (switchCommand) 
    { 
    case 1: 
        printf("\nEXIT\n"); 
        exit(0); 
    case 2: 
        chdir(parsed[1]);   //cd command 
        return 1;              
    default: 
        break; 
    } 
  
    return 0; 
} 
// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < 100; i++) 
    { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 
int processString(char* str, char** parsedString, char** parsedpipeString) 
{ 
  
    char* strpiped[2]; 
    int piped = 0; 
  
    piped = parsePipe(str, strpiped); 
  
    if (piped) { 
        parseSpace(strpiped[0], parsedString); 
        parseSpace(strpiped[1], parsedpipeString); 
  
    } else { 
  
        parseSpace(str, parsedString); 
    } 
  
    if (ownCmdHandler(parsedString)) 
        return 0; 
    else
        return 1 + piped; 
} 
void SystemCommands(char** parsed) 
{ 
    // Forking a child 
    pid_t pid = fork();  
  
    if (pid == -1) 
    { 
        printf("\nFailed forking child.."); 
        return; 
    } 
    else if (pid == 0) 
    { 
        if (execvp(parsed[0], parsed) < 0) 
        { 
            printf("\nCould not execute command.."); 
        } 
        exit(0); 
    }
    else 
    { 
        // waiting for child to terminate 
        wait(NULL);  
        return; 
    } 
} 
  
// Function where the piped system commands is executed 
void SystemCommandsPiped(char** parsed, char** parsedpipe) 
{ 
    // 0 is read end, 1 is write end 
    int pipefd[2];  
    pid_t p1, p2; 
  
    if (pipe(pipefd) < 0) 
    { 
        printf("\nPipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0)
     { 
        printf("\nCould not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // Child 1 executing.. 
        // It only needs to write at the write end 
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 
  
        if (execvp(parsed[0], parsed) < 0) 
        { 
            printf("\nCould not execute command 1.."); 
            exit(0); 
        } 
    } 
    else
     { 
        // Parent executing 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Child 2 executing.. 
        // It only needs to read at the read end 
        if (p2 == 0) { 
            close(pipefd[1]); 
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]); 
            if (execvp(parsedpipe[0], parsedpipe) < 0) { 
                printf("\nCould not execute command 2.."); 
                exit(0); 
            } 
        } else { 
            // parent executing, waiting for two children 
            wait(NULL); 
            wait(NULL); 
        } 
    } 
} 

int main()
{
	char inputString[1000];
	char *commands[100];
	char *commandpipe[100];
	int flag=0;
	initializeShell();  //return current user

	
 	while (1) 
	{ 
	// print shell line 
	printCurrentDirectory();   //print current directory using getcwd()
	// take input 
	if (Input(inputString)) 
	    continue; 
	// process 
	flag = processString(inputString, commands,commandpipe); 
	// execflag returns zero if there is no command 
	// or it is a builtin command, 
	// 1 if it is a simple command 
	// 2 if it is including a pipe. 
  
	// execute 
	if (flag == 1) 
	   SystemCommands(commands); 
  
	if (flag == 2) 
	   SystemCommandsPiped(commands,commandpipe); 
 	  
	 }
    return 0; 
}
