/* 
The following program is to calculate the area under the function of 1/(1+sq(x)) from 0 to 1. 
The expected answer is pi.After creating the basic function, it parallelises it.
Pseudocode
define h [(b-a)/n] where a, b are the end points of integration, n is the number of steps
for i = 0:n-1
sum=0
x = ((a+ih)+(a+(i+1)h)/2;
sum+=1/(1+square(x));
*/

#include <stdio.h>
#include <omp.h>
static long num_steps=100000000;
double step;
# define NUM_THREADS 400
void main()
{
	//sum, nthreads are defined outside the parallel region so that it can be accessible later on.
	int i, nthreads;
	double pi,sum[NUM_THREADS]; 
	step =1.0/(double) num_steps;
	omp_set_num_threads(NUM_THREADS);
	double begin= omp_get_wtime();
	#pragma omp parallel
	{
		int i,id,nthrds;
		double x;
		id=omp_get_thread_num();
		nthrds=omp_get_num_threads();
		if(id==0) nthreads=nthrds;
		for(i=id,sum[id]=0.0;i<num_steps;i+=nthrds)
		{
			x=(i+0.5)*step;
			sum[id]+=4.0/(1.0+x*x);
		}
	}
	double finish=omp_get_wtime();
	printf(" The value elapsed in the loop calculation with parallel code is %lf seconds \n", finish-begin);
	for(i=0,pi=0.0;i<nthreads;i++)
		pi+=sum[i]*step;
	printf("The value of the integral is : %f \n",pi);
	printf("The no. of threads allocates is : %d",nthreads);
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*int nthreads,numOfSteps=200;
		float sum[NUM_THREADS],area;
		float start=0,end=1;
		float stepSize=(end-start)/(float)numOfSteps;
		double begin= omp_get_wtime();
		omp_set_num_threads(NUM_THREADS);
		# pragma omp parallel
		{
		int id,nthrds;
		float x;
		id = omp_get_thread_num();
		nthrds=omp_get_num_threads;
		if(id==0) nthreads=nthrds;
		sum[0]=0;
		sum[1]=0;
		for (int i=id;i<numOfSteps;i+nthrds)
		{
		  x=((start+i*stepSize)+(start+(i+1)*stepSize))/2;
		  sum[id]+=(4/(1+x*x));
		}
		}
		double finish=omp_get_wtime();
		for (int i=0,area=0.0;i<nthreads;i++)
		{
		area+=sum[i]*stepSize;
		}
		printf("Sum value is %f \n", area);
		printf(" The value elapsed in the loop calculation with parallel code is %lf seconds \n", finish-begin);
		/*
		float sumNew=0;
		begin= omp_get_wtime();
		for (int i=0;i<numOfSteps;i++)
		{
		  float x=((start+i*stepSize)+(start+(i+1)*stepSize))/2;
		  sumNew+=(4/(1+x*x));
		}
		float areaNew = sumNew*stepSize;
		finish = omp_get_wtime();
		printf("Sum value is %f \n", areaNew);
		printf(" The value elapsed in the loop calculation without parallel code is %lf seconds \n", finish-begin);
		}
		*/

