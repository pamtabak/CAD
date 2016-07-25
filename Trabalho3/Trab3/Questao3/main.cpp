#include "mpi.h"
#include <stdio.h>

using namespace std;

// Compile: mpic++ -std=c++11 main.cpp -o main.out
// Execute: mpirun -np <#PROCESS> ./main.out

int main(int argc, char * argv[])
{
	MPI_Init(&argc, &argv);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int matrixDimension = 10;

	// Para cada rank, gerar matrizes A e B
	// Dimensao = 100x100 = 10000
	double ** a = new double*[matrixDimension];
	double ** b = new double*[matrixDimension];
	for (int i = 0; i < matrixDimension; i++)
	{
		a[i] = new double[matrixDimension];
		b[i] = new double[matrixDimension];
		for (int j = 0; j < matrixDimension; j++)
			a[i][j] = rank;
	}

	int sendPartner;
	if (rank == (size - 1))
		sendPartner = 0;
	else
		sendPartner = rank + 1;

	int receivePartner;
	if (rank == 0)
		receivePartner = size - 1;
	else
		receivePartner = rank - 1;

	MPI_Send(&a[0][0],matrixDimension * matrixDimension,MPI_DOUBLE,sendPartner,rank,MPI_COMM_WORLD);

	MPI_Status status;
	MPI_Recv(&b[0][0],matrixDimension * matrixDimension,MPI_DOUBLE,receivePartner,receivePartner,MPI_COMM_WORLD, &status);
	printf("Elemento da matrix b: %lf. Tarefa %d recebeu da tarefa %d\n", b[0][0], rank, receivePartner);

	for (int i = 0; i < matrixDimension; i++)
	{
		delete [] a[i];
		delete [] b[i];
	}
	delete [] a;
	delete [] b;

	MPI_Finalize();

	return 0;
}