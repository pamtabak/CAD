#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <omp.h>

int partition(int * a, int p, int r)
{
    int *lt = new int[r-p];
    int *gt = new int[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

#pragma omp parallel for
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }   
    }   

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }   

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }   

    delete lt, gt;
    return p + lt_n;
}

void quicksort(int * a, int p, int r)
{
    int div;

    if(p < r){ 
        div = partition(a, p, r); 
#pragma omp parallel sections
        {   
#pragma omp section
            quicksort(a, p, div - 1); 
#pragma omp section
            quicksort(a, div + 1, r); 
        }
    }
}

int random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Wrong number of parameters" << std::endl;
        exit(0);
    }

    int k    = atoi (argv[1]);
    int size = pow(2,k);

    int * array = new int[size];
   
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

    quicksort(array, 0, size - 1);

    for(i = 0;i < size; i++){
        std::cout << array[i] << std::endl;
    }
    printf("\n");
    return 0;
}