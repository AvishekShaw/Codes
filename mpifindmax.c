#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
const int arraySize = 100;
const int maxRange=5000000;
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
	MPI_Comm comm;
	MPI_Status status;
	int rank,size;
	double LARGE_NEGATIVE_NUMBER=-9999999;
	MPI_Init(&argc, &argv);
	comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);
	if (size!=2)
	{
		printf("This program is valid only for 2 processes \n");
		exit(0);
	}
	if (rank==0)
	{
		//printf("The size of the array matrix is %d \n", arraySize);
		A = (double*)malloc(arraySize*sizeof(double));
		//print(&A[0],arraySize);
		printf("\n");
		randomize(&A[0],arraySize);
		print(&A[0],arraySize);
		local_array=(double*)malloc(arraySize/2*sizeof(double));
		for (int i=0;i<arraySize/2;i++)
		{
			local_array[i]=A[i];
		}
		print(&local_array[0],arraySize/2);
		MPI_Send(A+arraySize/2, arraySize/2, MPI_DOUBLE,1,10,comm);
	}
	
	else
	{
		local_array=(double*)malloc(arraySize/2*sizeof(double));
		MPI_Recv(local_array, arraySize/2, MPI_DOUBLE, 0,10,comm, &status);
		print(&local_array[0],arraySize/2);
	}
	
	local_max=LARGE_NEGATIVE_NUMBER;
	for (int i=0;i<arraySize/2;i++)
	{
		if (local_array[i]>local_max) local_max=local_array[i];
	}
	//printf("The local max is %f", local_max);
	
	if (rank==1) MPI_Send(&local_max,1,MPI_DOUBLE, 0,15,comm);
	else
	{
		max=local_max;
		MPI_Recv(&rank1_max,1,MPI_DOUBLE,1,15,comm,&status);
		if (rank1_max>max) max=rank1_max;
		printf("the maxiumum no. is: %f \n",max);
	}
	MPI_Finalize();
}
