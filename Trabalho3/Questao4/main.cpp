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

	double a[1];
	a[0] = rank;
	double sum = 0.0;
	
	double b[1];

	int receivePartner;
	if (rank == (size - 1))
		receivePartner = 0;
	else
		receivePartner = rank + 1;

	int sendPartner;
	if (rank == 0)
		sendPartner = size - 1;
	else
		sendPartner = rank - 1;

	for (int i = 0; i < size; i++)
	{
		MPI_Send(a,1,MPI_DOUBLE,sendPartner,rank,MPI_COMM_WORLD);

		MPI_Status status;
		MPI_Recv(b, 1,MPI_DOUBLE,receivePartner,receivePartner,MPI_COMM_WORLD, &status);
		sum += b[0];
		printf("Rank = %d, SUM = %lf\n", rank, sum);	
		a[0] = b[0];
	}

	MPI_Finalize();

	for (int i = 0; i < matrixDimension; i++)
	{
		delete [] a[i];
		delete [] b[i];
	}
	delete [] a;
	delete [] b;

	return 0;
}