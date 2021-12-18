/*
This program is a variant of the type to be submitted for MPI assignment of DS 221.
This does not ask the other processes to stop once one of the processes has found 
the required no. Also, this is not reading input from the file. Hence, I need to change
it so that it can be submitted.
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <stdbool.h>
const int arraySize = 1000000;
const int maxRange=5000000;
const int num_procs=10;
void print(double *p, int size)
{
	for(int i=0;i<size;i++)
	{
		printf("%f  ",p[i]);
	}
	printf("\n");
}

void randomize(double*p, int size)
{
	srand(time(0));	
	for (int i=0;i<size;i++)
	{	
  		p[i]=(rand()%maxRange)+1;
	}
}


int main(int argc, char* argv[])
{
	double *A, *local_array;
	double max, local_max, rank1_max,i;
	bool found =0;
	MPI_Comm comm;
	MPI_Status status;
	int rank,size;
	double find=(rand()%maxRange)+1;
	MPI_Init(&argc, &argv);
	comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);
	/*if (size!=2)
	{
		printf("This program is valid only for 2 processes \n");
		exit(0);
	}
	*/
	if (rank==0)
	{
		//printf("The size of the array matrix is %d \n", arraySize);
		A = (double*)malloc(arraySize*sizeof(double));
		//print(&A[0],arraySize);
		printf("\n");
		randomize(&A[0],arraySize);
		//print(&A[0],arraySize);
		local_array=(double*)malloc(arraySize/num_procs*sizeof(double));
		for (int i=0;i<arraySize/num_procs;i++)
		{
			local_array[i]=A[i];
		}
		//print(&local_array[0],arraySize/2);
		for(int i=1;i<num_procs;i++)
		{
		MPI_Send(A+i*(arraySize/num_procs), arraySize/num_procs, MPI_DOUBLE,i,i,comm);
		}
	}
	
	else
	{
		local_array=(double*)malloc(arraySize/num_procs*sizeof(double));
		MPI_Recv(local_array, arraySize/num_procs, MPI_DOUBLE, 0,rank,comm, &status);
		//print(&local_array[0],arraySize/2);
	}
	
	for (int i=0;i<arraySize/num_procs;i++)
	{
		if (local_array[i]==find) 
		{
			printf("The number %f has been found at position %d by process %d \n",find,i,rank);
			found = 1;
			//exit(0);
			//MPI_Finalize();
		}
	}
	
	if (found==0) 
	{
	printf("The no. %f could not be found by process %d \n", find, rank);
	//exit(0);
	//MPI_Finalize();
	}
	MPI_Finalize();
	return 0;
}
