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
	        	C[i][j] = C[i][j] + matrixA[i][k] * matrixB[k][j]; 
	        	// C[i][j] = C[i][j] + matrixA[j][k] * matrixB[k][i]; // invertendo i com j
	        }
	    }
	}
}

void blockingMultiplyMatrixes(int** matrixA, int** matrixB, int matrixSize, int block)
{
	int **C = fillMatrix(matrixSize, 0); // filling matrixes with 0 in all positions

	int count = 0;
	for (int ii = 0; ii < matrixSize; ii += block)
	{
		for (int jj = 0; jj < matrixSize; jj += block)
		{
			for (int kk = 0; kk < matrixSize; kk += block)
			{
				for (int i = ii; i < min(matrixSize, ii + block); i++)
				{
				    for (int j = jj; j < min(matrixSize, jj + block); j++)
					{
						for (int k = kk; k < min(matrixSize, kk + block); k++)
						{
							C[i][j] = C[i][j] + matrixA[i][k] * matrixB[k][j];
						}
					}
				}
			}
		}
	}
}



int main(int argc, const char* argv[])
{
	//if(argc != 2)
	//{
	//	cout << "Wrong number of parameters!" << endl;
	//}
	//else
	//{
	chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();

	int matrixSize = 1000;

	int** matrixA = fillMatrix(matrixSize, 1);
	int** matrixB = fillMatrix(matrixSize, 1);	

	// multiplyMatrixes(matrixA, matrixB, matrixSize);
	blockingMultiplyMatrixes(matrixA, matrixB, matrixSize, 2);

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
	//}
	
	return 0;
}
