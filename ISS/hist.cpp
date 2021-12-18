

/*
LAST EDIT 10/11/2019 1724 Hrs. FINAL.

😀️PARALLELIZATION OF HISTOGRAM CALCULATON USING OPENMP
IN THIS ASSIGNMENT, YOU WILL CALCULATING AN HISTOGRAM FOR A GIVEN ARRAY OF NUMBERS AND FOR A GIVEN HISTOGRAM INTERVAL. FIRST GENERATE AN ARRAY OF 20,000 INTEGER NUMBERS BETWEEN 1 AND 20 AS AN INPUT ARRAY. HAVE ANOTHER ARRAY, CALLED THE HISTOGRAM ARRAY, WHOSE SIZE WILL BE EQUAL 20/(HISTOGRAM_INTERVAL). FOR EXAMPLE, IF THE HISTOGRAM INTERVAL IS 4, THEN THE HISTOGRAM ARRAY WILL BE A 5-ELEMENT ARRAY: THE COUNT OF THE INPUT NUMBERS BETWEEN 1-4 WILL BE STORED IN HISTOGRAM_ARRAY[0], THE COUNT OF THE INPUT NUMBERS BETWEEN 5-8 WILL BE STORED IN HISTOGRAM_ARRAY[1], AND SO ON. WRITE A SEQUENTIAL PROGRAM FOR CREATING THE HISTOGRAM ARRAY.

PARALLELIZE THE PROGRAM USING OPENMP WHERE DIFFERENT THREADS PROCESS DIFFERENT ELEMENTS OF THE INPUT ARRAY. BOTH THE INPUT ARRAY AND THE OUTPUT HISTOGRAM ARRAY ARE SHARED AMONG THE THREADS. AN OPENMP THREAD, WHEN PROCESSING AN ELEMENT IN THE INPUT ARRAY, INCREMENTS THE COUNT OF THE CORRESPONDING ELEMENT IN THE HISTOGRAM_ARRAY. THE MAIN THREAD FINALLY PRINTS THE COUNTS OF THE HISTOGRAM ARRAY.

CHECK THE CORRECTNESSS OF YOUR PARALLEL PROGRAM BY COMPARING THE OUTPUT WITH THAT OF THE SEQUENTIAL PROGRAM. SHOW THE TIMINGS OF THE SEQUENTIAL AND THE OPENMP VERSION FOR DIFFERENT NUMBER OF OPENMP THREADS (2, 4, 8, 16, 32) AND FOR HISTOGRAM INTERVALS, NAMELY, 1, 2, 4, 5 AND 10. FOR EACH EXPERIMENT WITH A FIXED NUMBER OF THREADS, AND FOR THE SEQUENTIAL PROGRAM, RUN 5 TIMES, AND OBTAIN THE AVERAGE EXECUTION TIME ACROSS THESE 5 RUNS.

PREPARE A REPORT CONTAINING:
METHODOLOGY
EXPERIMENTAL SETUP
RESULTS CONTAINING EXECUTION TIMES AND SPEEDUP WITH THE ABOVE OPTIONS, BOTH AS TABLES AND GRAPHS WITH X AND Y AXES PROPERLY LABELED.
OBSERVATIONS. 
*/


#include <iostream>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
const int maxRange=20; // Max range of random nos. (Min range = 1)
const int size=500000000;     // Size of the integer array of random nos.
int *intArray=(int*) malloc(size*sizeof(int));

// function to randomize the integer array. srand(1) is taken to make sure
// that the results are reproducible
void randomize(int*p, int size)
{
	srand(1);	
	for (int i=0;i<size;i++)
	{	
  		p[i]=(rand()%maxRange)+1;
	}
}

// function to print the values of the array
void print(int*p, int size)
{
	for(int i=0;i<size;i++)
	{
		cout<<p[i]<<" ";
	}
	cout<<endl;
}

// function to initialize an array to the value of 0
void init(int*p, int size)
{
	for (int i=0;i<size;i++)
	{	
  		p[i]=0;
	}
}

int main()
{
	int histIntervalRange[] ={1,2,4,5,10}; // to cycle through the bucket sizes given in the question
	int nthreads; 
	double begin, finish;
	for (int s:histIntervalRange)
	{
		cout<<"Beginning calculations with histogram bucket size : "<<s<<endl;
		int intervalSize=s;
		int histSize=maxRange/intervalSize;
		int histArray[histSize];
		randomize(&intArray[0],size);
	
		// To initialize the histogram to 0
		init(&histArray[0],histSize);
		
		//Serial execution to check the correctness and time of execution
		begin= omp_get_wtime();	
		for (int l=0;l<size;l++)
				{
					int t=(intArray[l]-1)/intervalSize;
					histArray[t]++;
				}
		finish=omp_get_wtime();
		printf("The time elapsed in histogram calculation with serial code is %lf seconds \n", finish-begin);	
		cout<<"The histogram array with serial execution is: \n";
		print(&histArray[0],histSize);
		cout<<endl;
		
		// To re-initialize the histogram with 0 after serial execution for parallel execution
		init(&histArray[0],histSize);
		
		// to create the histogram and to parallelize the region
		int i, id;
		
		//To cycle through the number of threads
		for (int numthreads=2;numthreads<33;numthreads*=2)
		{	
			// We need to create a temporary histogram array, initialize it to 0 and declare it as shared(as the facility of array reduction is not available)		
			int tempHistArray[numthreads][histSize];
			for (int k=0;k<numthreads;k++)
			{
				for (int j=0;j<histSize;j++)
				{
					tempHistArray[k][j]=0;
				}
				
			}
			// beginning of the timing region
			begin= omp_get_wtime();	
			#pragma omp parallel default(none) shared(intArray,intervalSize,nthreads,cout,tempHistArray,histArray) private(i,id) num_threads(numthreads)
			{
				id=omp_get_thread_num();
				nthreads=omp_get_num_threads();
				#pragma omp for
				for (int i=0;i<size;i++)
				{
					int t=(intArray[i]-1)/intervalSize;
					tempHistArray[id][t]++;
				}
			}
			
			 //To reduce the elements of tempHistArray to histArray by adding the elements columnwise.
			for (int k=0;k<histSize;k++)
			{
				for (int j=0;j<numthreads;j++)
				{
					histArray[k]+=tempHistArray[j][k];
				}
				
			}
			finish=omp_get_wtime();
			
			cout<<"The no. of threads given by the processor was:"<<nthreads<<endl;
			cout<<"The time elapsed in histogram calculatin with no. of threads "<<nthreads<<" is "<<finish-begin<<" seconds \n";
			cout<<"The histogram array with no. of threads "<<nthreads<<" is: \n";
			print(&histArray[0],histSize);
			cout<<endl;
			// Re-initializing the histArray to 0 to make sure that the next thread encounters a tabula-rasa
			init(&histArray[0],histSize);
		}
	cout<<"Calculations with histogram bucket size : "<<s<<" finished "<<endl;	
	cout<<endl;
	}
	
	
return 0;
}


/*
My Ideas for the assignment:

1. Let us declare the tempHistArray of size NumThreads*histhistSize. ie. 
if there are 6 threads and 5 histogram intervals, let us declare a 6X5 matrix, 
let each thread updateits own row. And in the end, we will add all those rows 
column wise to get the final sum. But this turned out to be a bad strategy.

2. It is much better to use the reduction strategy. 

3. I have to find out a way to make the loop for the no. of threads work

4. Find out if you need to print the no. of threads, if so, i might have to waste some time.

5. the facility of array reduction is not available in ubuntu 16.04. hence I need to declare
a tempHistArray which will be shared among all the threads and it will be finally reduced columnwise
to form the histogram array.

Ideas that were tried but could not be used
1. direct reduction of histogram array(not supported by ubuntu 16.04 on turing cluster
2. locks to avoid the use of tempHistArray and let the threads directly access the histArray. However, it had poorer time performance.
*/


