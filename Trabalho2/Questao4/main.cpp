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
 	
 	int i, j, temp;       
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
        temp   = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }
	quickSortWithoutOMP(vec, i);
	quickSortWithoutOMP(vec + i, size - i);
}

int partition (int *vec, int init, int final)
{
	int *lte = new int[final - init]; // less or equal than
    int *gt  = new int[final - init]; // greater than
    int i;
    int j;
    int pivot = vec[final];
    
    int lte_n = 0;
    int gt_n  = 0;

    #pragma omp parallel default (none) shared(init, final, vec, lte, lte_n, gt, gt_n, pivot) private(i,j)
    {
    	#pragma omp for
    		for(i = init; i < final; i++)
		    {
		        if(vec[i] < vec[final])
		        {
		            lte[lte_n++] = vec[i];
		        }
		        else
		        {
		            gt[gt_n++] = vec[i];
		        }   
		    }   

		    for(i = 0; i < lte_n; i++)
		    {
		        vec[init + i] = lte[i];
		    }   

		    vec[init + lte_n] = pivot;

		    for(j = 0; j < gt_n; j++)
		    {
		        vec[init + lte_n + j + 1] = gt[j];
		    }   
    }
    // #pragma omp parallel for
    // for(i = init; i < final; i++)
    // {
    //     if(vec[i] < vec[final])
    //     {
    //         lte[lte_n++] = vec[i];
    //     }
    //     else
    //     {
    //         gt[gt_n++] = vec[i];
    //     }   
    // }   

    // for(i = 0; i < lte_n; i++)
    // {
    //     vec[init + i] = lte[i];
    // }   

    // vec[init + lte_n] = pivot;

    // for(j = 0; j < gt_n; j++)
    // {
    //     vec[init + lte_n + j + 1] = gt[j];
    // }   

    delete lte, gt;
    return init + lte_n;
}

void quickSort (int *vec, int init, int final)
{
	int div;

	if (init < final)
	{
		div = partition(vec, init, final); 
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				quickSort(vec, init, div - 1);
			}
			#pragma omp section
			{
				quickSort(vec, div + 1, final);	
			}
		}
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
		// quickSortWithoutOMP(array, size);
		// for (int i = 0; i < size; i++)
		// {
			// cout << array[i] << endl;
		// }
	}

	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> endTimeSpan = chrono::duration_cast<chrono::duration<double> >(endTime - startTime);
	printf("end: %lf secs\n", endTimeSpan.count());

	delete array;

	return 0;
}