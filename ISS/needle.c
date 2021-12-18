/*
This program is for assignment 3 of MPI of DS 221. We need to read a series of 1 million nos.
from a file. the nos. are integers between 1 and 5 million. The purpose is to find a no. in 
the big array. If one of the processes finds it, it will inform the others about it and the 
others will stop searching. we have to make this run for 50 random nos. and report the average
time taken for the execution of these 50 finds. Also, we have to run the program for
differerent no. of processes i.e. 1,2,4,8,16,32,64.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <stdbool.h>
const int arraySize = 1000000;
const int maxRange=100;
const int num_procs=64;

int main(int argc, char** argv)
{
	long *A, *local_array, *queryArray;
	int rank,flag=0,size;
	long blockSize=arraySize/num_procs;
	long global_pos=-1,local_pos=-1, temp_pos=-1;
	long find;
	
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);	

	A = (long*)malloc(arraySize*sizeof(long));
	queryArray = (long*)malloc(50*sizeof(long));
	FILE *myFile;
	myFile=fopen("q2-sample-input.txt","r");
	for (int l=0;l<1000000;l++)
	{
		fscanf(myFile,"%ld",&A[l]);
	}
	for (int p=0;p<50;p++)
	{
		fscanf(myFile,"%ld",&queryArray[p]);
	}
	fclose(myFile);
	
	local_array=(long*)malloc(blockSize*sizeof(long));
	MPI_Scatter(A,blockSize,MPI_LONG,local_array,blockSize,MPI_LONG,0,MPI_COMM_WORLD);	
	MPI_Barrier(MPI_COMM_WORLD);
	double begin, finish;
	FILE *fptr = fopen("output position.txt","w");
	double time[num_procs];
	begin=MPI_Wtime();
	for (int k=0;k<50;k++)
	{
		find=queryArray[k];
		MPI_Irecv(&global_pos,1,MPI_LONG,MPI_ANY_SOURCE,k,MPI_COMM_WORLD,&request);
		local_pos=-1;global_pos=-1;temp_pos=-1;flag=0;
		for(int i=0;i<blockSize;i++)
		{
			if (local_array[i]==find) 
			{
				// Send to all the processes that I have found the element
				local_pos=(rank*blockSize)+i;
				for (int j=0;j<rank;j++)				MPI_Send(&local_pos,1,MPI_LONG,j,k,MPI_COMM_WORLD);
				for (int j=rank+1;j<num_procs;j++)  MPI_Send(&local_pos,1,MPI_LONG,j,k,MPI_COMM_WORLD);
				if (rank==0) 							 	global_pos=local_pos;
				MPI_Cancel(&request);
				break;
			}
		
			else
			{
				MPI_Test(&request, &flag, &status);
				if (flag==1)
				{
					MPI_Wait(&request, &status);
					break;
				}
			}
	  }
	  finish=MPI_Wtime();
	  MPI_Barrier(MPI_COMM_WORLD);
	  if (rank==0) 	
	  {
	  		fprintf(fptr,"%ld \n",global_pos);
	  	}
	}
	time[rank]=finish-begin;
	printf(" %lf \n",time[rank]);
	fclose(fptr);
	MPI_Finalize();
	return 0;
}

