#include<string.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h> 
#include <sys/shm.h>
#include <time.h>
#include <stdlib.h>


struct buffer
{
char buffer1[50];
char buffer2[50];

};

sem_t *semaphore1;
sem_t *semaphore2;

const key_t shm_key =1800;


int main(int argc,char*argv[])
{

   int mem_id = shmget(shm_key,sizeof(struct buffer),0600|IPC_CREAT|IPC_EXCL);
    if(mem_id < 0)
    {
    	printf("Shared memory creating failed\n");
    	return 1;
    }
	int id_s1=shmget(1111, 1024, 0666 | 0600|IPC_CREAT|IPC_EXCL);
	int id_s2= shmget(1112, 1024, 0666 | 0600|IPC_CREAT|IPC_EXCL);
	semaphore1= (sem_t*) shmat(id_s1, NULL, 0);
   	semaphore2= (sem_t*) shmat(id_s2, NULL, 0);
			
	sem_init(semaphore1,1,1); 
        sem_init(semaphore2,1,0);

int pid1, pid2, pid3,pid4; 

 FILE *fptr1;
 FILE *fptr2;
 char ch;
 char *f1=argv[1];
 char *f2=argv[2];



  pid1=fork(); //child1
	if(pid1==0)
	{
	   char str[20];
		
	  if ((fptr1 = fopen(f1,"r")) == NULL)
	  {
	       printf("Error! opening file 1\n");
	
	       // Program exits if the file pointer returns NULL.
	       exit(1);
	  }
	  else
	  {
		printf("FILE 1 is opened\n");
	
			while( fgets ( str, 20, fptr1 ) != NULL ) 
			{
			    printf("\n");
			    printf("file 1= ");
			    printf( "%s" , str) ; 
			  
			 } 
			  
		
			fclose(fptr1) ; 
	  }
		sem_wait(semaphore1); 
		printf("\nProcess 1 writing  first 10=\n"); 
		
		void* memory = shmat(mem_id, NULL ,0);
      	
      		struct buffer* read = (struct buffer*) memory;
      		

		strncpy(read->buffer1,str,10);
		read->buffer1[10]='\0';		
		sem_post(semaphore2); 
		shmdt(memory); 
			
	}
	else
	{
	   pid2=fork(); //child2
	   if(pid2==0)
	   {
		//sleep(2);
             char str2[20];

	      if ((fptr2 = fopen(f2,"r")) == NULL)
  	      {
       		printf("Error! opening file 1\n");
		// Program exits if the file pointer returns NULL.
      		 exit(1);
  	      }
  	     else
   	     {
 		printf("FILE 2 is opened\n");

			while( fgets ( str2, 20, fptr2 ) != NULL ) 
			{
			    printf("\n");
			    printf("file 2= ");
			    printf( "%s" , str2) ; 
			  
			 } 
			  
		
			fclose(fptr2) ; 
   	     }

	        sem_wait(semaphore2); 
		printf("\nProcess 2 writing first 10=\n"); 
		
		void* memory = shmat(mem_id, NULL ,0);
      	

		struct buffer* read = (struct buffer*) memory;

		strncat(read->buffer1,str2,10);
		read->buffer1[20]='\0'; 
		shmdt(memory); 
					


	   }
           else	
	   {
		pid3=fork();//child3
                if(pid3==0)
		{
	
		sleep(2);  
		
				
		
		printf("\nProcess 3 reading=\n"); 
		
		void* memory= shmat(mem_id, NULL ,0);
      	

		struct buffer* read = (struct buffer*) memory;

		strcat(read->buffer2,read->buffer1); 
		shmdt(memory); 
		
		}
		else
		{
		  pid4=fork();//child4
		  if(pid4==0)
		  {
		sleep(3); 
				
			
		printf("\nProcess 4 reading and displaying \n"); 
		
		void* memory = shmat(mem_id, NULL ,0);
      		

		struct buffer* read = (struct buffer*) memory;
		printf("\n"); 
		printf( "%s" , read->buffer2) ;
		printf("\n");
	
		shmdt(memory); 
		
		shmctl(mem_id,IPC_RMID,NULL);
					
	
		  }
		  else
		  { 
                   sleep(4);
 		  }


		}
	   }


	}

   sem_destroy(semaphore1);
   sem_destroy(semaphore2);
 
   shmdt(semaphore1);
   shmdt(semaphore2);

 
   shmctl(id_s1, IPC_RMID, NULL);
   shmctl(id_s2, IPC_RMID, NULL);

}
