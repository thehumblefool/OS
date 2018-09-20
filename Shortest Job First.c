/*
     Write a program in C which reads input CPU bursts from a the first line of a text file named as
     CPU_BURST.txt. Validate the input numbers whether the numbers are positive intergers or not.
     Consider the numbers as CPU burst. If there are 5 positive integers in the first line of the text file then
     the program treat those argument as required CPU bust for P1, P2, P3, P4, and P5 process and calculate
     average waiting time and average turnaround time. Consider used scheduling algorithm as SJF and
     same arrival time for all the processes.
*/

#include<stdio.h>

int main()
{
	int CPU_Burst[100]={0},TAT[100],WT[100],P[100];
	float Avg_TAT,Avg_WT;
	int temp,i,j,count=0;

	FILE *fp=fopen("CPU_BURST.txt","r"); //Opening the File

	if(fp==NULL)
    {
    	printf("\nFile does not exist \n\n");
    	return 1;
  	}

  	//Read CPU Burts from file, validate and store in an Array
  	while(fscanf(fp,"%d",&temp)==1)
  	{
    	if(temp<0)
    	{
      		printf("\nCPU Burst read from file is negative \n\n");
      		return 1;
    	}
    	P[count]=count+1;
    	CPU_Burst[count]=temp;
    	count++;
  	}

  	fclose(fp); //Close the file

  	//Insertion Sort to sort CPU Bursts in Ascending Order
  	for(i=1;i<count;i++)
	{
		j=i;
		while(j>0 && CPU_Burst[j]<CPU_Burst[j-1])
		{
			temp=CPU_Burst[j];
			CPU_Burst[j]=CPU_Burst[j-1];
			CPU_Burst[j-1]=temp;

      			//Arranging the Process's number based on the order of CPU Bursts
      			temp=P[j];
      			P[j]=P[j-1];
      			P[j-1]=temp;

			j--;
		}
	}

  	temp=0;

  	//Calculation of Waiting Time and Turn Around Time considering Arrival time of all processes as 0(Zero) according to the question
  	for(i=0;i<count;i++)
  	{
    	WT[i]=temp; //Waiting Time will be Sum of the CPU Bursts of all the processes executed before it as Arrival Time of all the processes is Zero

    	temp+=CPU_Burst[i];

    	TAT[i]=temp; //Turn Around Time will be Sum of the CPU Bursts of all the processes executed before it and CPU Burst of it

    	Avg_WT+=WT[i]; //Adding Waiting Time of all the processes
    	Avg_TAT+=TAT[i]; //Adding Turn Around Time of all the processes
  	}

  	//Calculation of Average Waiting Time and Average Turn Around Time
  	Avg_WT=Avg_WT/count;
  	Avg_TAT=Avg_TAT/count;

  	printf("\nPID\tBurst\t Waiting Time\t   Turn Around Time \n___________________________________________________________\n");
  	for(i=0;i<count;i++)
    	printf("P%d\t  %d\t    %d\t\t\t%d\n",P[i],CPU_Burst[i],WT[i],TAT[i]);
  	printf("\nAverage Waiting Time     : %.2f\nAverage Turn Around Time : %.2f\n\n",Avg_WT,Avg_TAT);
  	return 0;
}
