#include <iostream>
#include <math.h>
#include <cstring>
#include <cstdlib>
#include <chrono>

using namespace std;

int** fillMatrix(int matrixSize, int fill)
{
	int** matrix = new int*[matrixSize];	

	for (int i = 0; i < matrixSize; i++)
	{
		matrix[i] = new int[matrixSize];
		for (int j = 0; j < matrixSize; j++)
		{
			matrix[i][j] = fill;	
		}
	}
	return matrix;
}

void multiplyMatrixes(int** matrixA, int** matrixB, int matrixSize)
{
	int** C = new int*[matrixSize];
	for (int i = 0; i < matrixSize; i++)
	{
		C[i] = new int[matrixSize];
	}

	for (int j = 0; j < matrixSize; j++)   // Loop J
	{
    	for(int i = 0; i < matrixSize; i++) // Loop I
	    {   
	    	C[i][j] = 0;
	    	for(int k = 0; k < matrixSize; k++) // Loop K
	    	{
	        	C[i][j] += matrixA[i][k] * matrixB[k][j];
	        }
	    }
	}
}


int main(int argc, const char* argv[])
{
	if(argc != 2)
	{
		cout << "Wrong number of parameters!" << endl;
	}
	else
	{
		chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();

		int matrixSize = atoi(argv[1]);

		int** matrixA = fillMatrix(matrixSize, 1);
		int** matrixB = fillMatrix(matrixSize, 1);

		multiplyMatrixes(matrixA, matrixB, matrixSize);

		chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
		chrono::duration<double> endTimeSpan = chrono::duration_cast<chrono::duration<double> >(endTime - startTime);
		printf("end: %lf secs\n", endTimeSpan.count());

		for (int i = 0; i < matrixSize; ++i)
		{
			delete [] matrixA[i];
			delete [] matrixB[i];
		}
		delete [] matrixA;
		delete [] matrixB;
	}
	
	return 0;
}
