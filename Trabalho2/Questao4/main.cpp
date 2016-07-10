#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <omp.h>

using namespace std;

chrono::high_resolution_clock::time_point startTime;

int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void quickSortWithoutOMP (int *vec, int size) 
{
    if (size < 2)
    {
    	return;
    }
 	
 	int i, j;
    int pivot = vec[size / 2];
    for (i = 0, j = size - 1;; i++, j--)
    {
		while (vec[i] < pivot)
        {
        	i++;
        }
		while (pivot < vec[j])
		{
			j--;
		}
        if (i >= j)
        {
        	break;
        }
        swap(vec[i], vec[j]);
    }
	quickSortWithoutOMP(vec, i);
	quickSortWithoutOMP(vec + i, size - i);
}

int partition(int *vec, int init, int final)
{
	int pivot = vec[init];
	int i;
	int j;
	// while(1)
	for (i = init + 1, j = final ;; i++, j--)
	{
		while(i < final && pivot >= vec[i])
	    	i++;
		while(pivot < vec[j])
	    	j--;
		if(i < j)
		{
			swap(vec[i], vec[j]);
		}
		else
		{
			swap(vec[init], vec[j]);
			return j;
		}
	}
}


void quickSort (int *vec, int init, int final)
{
	int div;

	if (init >= final)
	{
		return;
	}

	div = partition(vec, init, final); 
	#pragma omp parallel sections num_threads(8)
	{
		#pragma omp section 
			quickSort(vec, init, div - 1);
		#pragma omp section
			quickSort(vec, div + 1, final);
	}
}

int main(int argc, const char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of parameters" << endl;
		exit(0);
	}

	startTime = chrono::high_resolution_clock::now();
	int k    = atoi (argv[1]);
	int size = pow(2,k);

	int * array = new int[size];

	if (k == 1)
	{
		// do nothing
	}
	else
	{
		srand(time(NULL));
		
		for (int j = 0; j < 10; j++)
		{
			// Initializing array with random values
			int i;
			#pragma omp parallel default (none) private (i) shared (size, array)
			{
				#pragma omp for
				for (i = 0; i < size; i++)
				{
					array[i] = random(1,10000000);
				}
			}

			quickSort(array, 0, size - 1);
			
		    // for (int i = 0; i < size; i++)
		    // {
		    // 	cout << array[i] << endl;
		    // }
			// quickSortWithoutOMP(array, size);
		}
	}

	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> endTimeSpan = chrono::duration_cast<chrono::duration<double> >(endTime - startTime);
	printf("end: %lf secs\n", endTimeSpan.count() / 10);

	delete array;

	return 0;
}