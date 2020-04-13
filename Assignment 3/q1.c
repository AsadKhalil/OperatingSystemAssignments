#include<pthread.h>
#include<stdio.h>
#include <time.h>
#include <semaphore.h> 
#include<string.h>
#include <unistd.h>
#include <stdlib.h>



int potentialCPatients=1;
int present=1;
int last=1;

sem_t coronaPatients;
sem_t fluPatients;
sem_t mutex;


void coronapatientTest()
{
	 
		//int rand=rand()%2;
		//last=present;
		//present=rand;
	printf("Testing of Corona Patient");
	//for(int i=0;i<2;i++)
	//{		
	sem_wait(&coronaPatients);

	//}



}

void coronaTestCenter()
{
	printf("There");
   int r=rand() % 2;  
   if (r==0)
   { 
   	 sem_post(&fluPatients);
   	 potentialCPatients--;

   }
   else
   {
      sem_post(&coronaPatients);
      potentialCPatients--; 
   }
}

void * patient()
{
	potentialCPatients++;
	pthread_exit(NULL);
}




int main(int argc, char const *argv[])
{

	sem_init(&mutex, 0, 1);
	sem_init(&coronaPatients,0,0);
	sem_init(&fluPatients,0,0);

	pthread_t tid;
	int n;

	printf("Enter the no of threads you want run for \n");
	scanf("%d",&n);


	printf("Entered Numbered is: %d \n",n);


	for(int i=0;i<n;i++)
	{
		 
          pthread_create(&tid,NULL,&patient,NULL);   
         
	}
    printf("No of patient counts are %d\n",potentialCPatients);


    for (int i = 0; i < potentialCPatients; i++)
    {
    	coronaTestCenter();
    	/* code */
    }

	int val;

    
 	 while (val>0){
	printf("there");
    	coronapatientTest();
    	val--;
	}

	return 0;
}
