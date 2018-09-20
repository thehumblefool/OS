/*
   ASSIGNMENT COMPLETION PROBLEM
      There are 3 student processes and 1 teacher process. Students are supposed to do their assignments and
      they need 3 things for that-pen, paper and question paper. The teacher has an infinite supply of all the
      three things. One students has pen, another has paper and another has question paper. The teacher
      places two things on a shared table and the student having the third complementary thing makes the
      assignment and tells the teacher on completion. The teacher then places another two things out of the
      three and again the student having the third thing makes the assignment and tells the teacher on
      completion. This cycle continues. WAP to synchronise the teacher and the students.
*/

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>

/*
    0 - Student with Pen
    1 - Student with Paper
    2 - Student with Question Paper
*/

//Required Semaphores
sem_t Teacher; //Initialised with 1

sem_t Student_With_Pen; //Initialised with 0
sem_t Student_With_Paper; //Initilised with 0
sem_t Student_With_Q_Paper; //Intialised with 0

void* teacher();
void* studentWithPen();
void* studentWithPaper();
void* studentWithQPaper();

void main()
{
	pthread_t t[4]; //1 thread for Teacher and 3 threads for Students 

  	sem_init(&Teacher,0,1);
  	sem_init(&Student_With_Pen,0,0);
  	sem_init(&Student_With_Paper,0,0);
  	sem_init(&Student_With_Q_Paper,0,0);

  	pthread_create(&t[0],NULL,teacher,NULL);
  	pthread_create(&t[1],NULL,studentWithPen,NULL);
  	pthread_create(&t[2],NULL,studentWithPaper,NULL);
  	pthread_create(&t[3],NULL,studentWithQPaper,NULL);

  	pthread_join(t[0],NULL);
  	pthread_join(t[1],NULL);
  	pthread_join(t[2],NULL);
  	pthread_join(t[3],NULL);

}

void* teacher()
{
  	while(1)
  	{
    	sem_wait(&Teacher);

    	int stu_no=rand()%3; //Selecting Student at random

    	switch(stu_no)
    	{
      		case 0 :	printf("\n Teacher Kept Paper and Question paper on the table \n");
                		sem_post(&Student_With_Pen); //Signal the Respective Student i.e Student with Pen
                		break;

      		case 1 :  	printf("\n Teacher Kept Pen and Question paper on the table \n");
                		sem_post(&Student_With_Paper); //Signal the Respective Student i.e Student with Paper
                		break;

      		case 2 :  	printf("\n Teacher Kept Pen and Paper on the table \n");
                		sem_post(&Student_With_Q_Paper); //Signal the Respective Student i.e Student with Question Paper
                		break;

      		default:  	break;
    	}

    	sleep(2);
  	}
}

void* studentWithPen()
{
  	while(1)
  	{
    	sem_wait(&Student_With_Pen);
    
    	printf(" Student with Pen picked up Paper and Question Paper from the table and Started Assignment \n");

    	printf(" Student with Pen completed his Assignment \n Informing the Teacher \n");

    	sem_post(&Teacher); //Signal the Teacher after Completion of the Assignment

    	sleep(2);
  	}
}

void* studentWithPaper()
{
  	while(1)
  	{
    	sem_wait(&Student_With_Paper);

    	printf(" Student with Paper picked up Pen and Question Paper from the table and Started Assignment \n");
    
    	printf(" Student with Paper completed his Assignment \n Informing the Teacher \n");

    	sem_post(&Teacher); //Signal the Teacher after Completion of the Assignment

    	sleep(2);
  	}
}

void* studentWithQPaper()
{
  	while(1)
  	{
    	sem_wait(&Student_With_Q_Paper);

    	printf(" Student with Question paper picked up Pen and Paper from the table and Started Assignment \n");

    	printf(" Student with Question Paper completed his Assignment \n Informing the Teacher \n");
    
    	sem_post(&Teacher); //Signal the Teacher after Completion of the Assignment

    	sleep(2);
  	}
}
