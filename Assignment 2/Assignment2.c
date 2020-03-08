#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

#define P1READ     0
#define P1WRITE    1

int main(int argc,char*argv[])
{
	int fd[2];
	pid_t pid1,pid2;
	char message[]=" Hello There";
	pipe(fd);
	pid1=fork();
	if(pid1==-1)
	{
	printf("Error child is not created");
	}
	else if(pid1==0)
	{
	char message1[20];
	printf("CHILD1\n");
	close(fd[P1WRITE]);  // Close writing end of first pipe 
  
        read(fd[P1READ], message1, strlen(message)+1); 
  	printf("%s\n",message1);
	}
	else if(pid1>0)
	{
	  	pid2=fork();
		if(pid2==-1)
		{ 
		 perror("FORK()");
       		}
		else if(pid2==0)
		{
		char message2[20];	
		printf("CHILD2\n");
		close(fd[P1WRITE]);  // Close writing end of first pipe 	  
	        read(fd[P1READ], message2, strlen(message)+1); 
  		printf("%s\n",message2);
		}
		else if(pid2>0)	
		{}
	 close(fd[P1READ]);
	 write(fd[P1WRITE], message, strlen(message)+1); 
         close(fd[P1WRITE]); 	
	 wait(NULL); 
	}
}
