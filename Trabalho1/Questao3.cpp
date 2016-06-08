#include <iostream>
#include <math.h>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <algorithm>    // std::max, std::min

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

	for(int i = 0; i < matrixSize; i++) // Loop I
	{
    	for (int j = 0; j < matrixSize; j++)   // Loop J
	    {   
	    	C[i][j] = 0;
	    	for(int k = 0; k < matrixSize; k++) // Loop K
	    	{
	        	// C[i][j] = C[i][j] + matrixA[i][k] * matrixB[k][j];
	        	C[i][j] = C[i][j] + matrixA[j][k] * matrixB[k][i]; // invertendo i com j
	        }
	    }
	}
}

// void blockingMultiplyMatrixes(int** matrixA, int** matrixB, int matrixSize, int block)
// {
// 	int** C = new int*[matrixSize];
// 	for (int i = 0; i < matrixSize; i++)
// 	{
// 		C[i] = new int[matrixSize];
// 	}

// 	for (int jj = 0; jj < matrixSize; jj += block)
// 	{
// 		for (int ii = 0; ii < matrixSize; ii += block)
// 		{
// 			for (int kk = 0; kk < matrixSize; kk += block)
// 			{
// 				for (int j = jj; min(matrixSize, jj + b - 1); j++)
// 				{
// 					for (int i = ii; min(matrixSize, ii + b - 1); i++)
// 					{
// 						for (int k = kk; min(matrixSize, kk + b - 1); k++)
// 						{
// 							C[i][j] = C[i][j] + matrixA[i][k] * matrixB[k][j];
// 							// C[i][j] = C[i][j] + matrixA[j][k] * matrixB[k][i]; // invertendo i com j
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }

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
