#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int npes,myrank;
	int a=2;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	if(myrank==0) printf(" Hello this is process 0s \n");
	if(myrank!=0)
	printf(" From process %d out of %d, Hello World \n", myrank,npes);
	MPI_Finalize();
}
