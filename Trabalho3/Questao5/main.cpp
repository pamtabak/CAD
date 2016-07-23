#include "mpi.h"
#include <stdio.h>

#define N 4

using namespace std;

// Compile: mpic++ -std=c++11 main.cpp -o main.out
// Execute: mpirun -np <#PROCESS> ./main.out

void fill_matrix(int matrix[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matrix[i][j] = 1;
		}
	}
}


int main(int argc, char * argv[])
{	
	int a[N][N], b[N][N], result[N][N];
	int tag = 10;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int from = rank * N / size;
	int to   = (rank + 1) * N / size;

	// Count e um multiplo de N
	int count = N*N/size;

	// Processo mestre
	if (rank == 0)
	{
		// O processo mestre deve criar as matrizes A e B
		fill_matrix(a);
		fill_matrix(b);
	}
	

	// Todos as tarefas precisam ter a matriz B inteira.
	MPI_Bcast(b, N*N, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(a, count, MPI_INT, a[from], count, MPI_INT, 0, MPI_COMM_WORLD);

	// Cada processo deve calcular uma porcao da multiplicacao matricial AxB
	for (int x = from; x < to; x++)
	{
		for (int y = 0; y < N; y++)
		{
			result[x][y] = 0;
			for (int z = 0; z < N; z++)
			{
				result[x][y] += a[x][z]*b[z][y];
			}
		}
	}

	// Recolha as porcoes dos calculos para o processo mestre
	MPI_Gather (result[from], count, MPI_INT, result, count, MPI_INT, 0, MPI_COMM_WORLD);

	// O processo mestre deve imprimir o resultado
	if (rank == 0)
	{
		for (int x = 0; x < N; x++)
		{
			for (int y = 0; y < N; y++)
			{
				cout << result[x][y] << endl;
			}
		}
	}

	MPI_Finalize();

	return 0;
}