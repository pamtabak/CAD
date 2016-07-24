#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define N 100000000
#define F 30
#define J 14

// Compile: mpic++ -std=c++11 main.cpp -o main.out
// Execute: mpirun -np <#PROCESS> ./main.out


void fill_vector(int matrix[N], int x, int size)
{
	for (int i = 0; i < size; i++)
	{
    matrix[i] = x;
	}
}

int a[N], b[N];

int main(int argc, char * argv[])
{
	MPI_Init(&argc, &argv);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

  // necessario ser double pois para arrays muito grandes é possivel ocorrer overfloat do int;
  double result[size];

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int from = rank * N / size;
	int to   = (rank + 1) * N / size;

	// Count e um multiplo de N
	int count = N/size;

	// Processo mestre
	if (rank == 0)
	{
		// O processo mestre deve criar as matrizes A e B
		cout << "trying to allocate" << endl;
		fill_vector(a, J, N);
		fill_vector(b, F, N);
		cout << "allocated" << endl;
	}


	// Todos as tarefas precisam ter a matriz B inteira.
	// MPI_Bcast(b, N*N, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&a, count, MPI_INT, &a[from], count, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&b, count, MPI_INT, &b[from], count, MPI_INT, 0, MPI_COMM_WORLD);

	// Cada processo deve calcular uma porcao da multiplicacao matricial AxB
  result[rank] = 0;

	for (int x = from; x < to; x++)
	{
    result[rank] += a[x] * b[x];
	}

	// Recolha as porcoes dos calculos para o processo mestre
	MPI_Gather (&result[rank], 1, MPI_DOUBLE, &result, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	// O processo mestre deve imprimir o resultado
	if (rank == 0)
	{
    double total = 0;
		for (int x = 0; x < size; x++)
		{
      cout << result[x] << endl;
      total += result[x];
		}
    cout << total << endl;
	}

	MPI_Finalize();

	return 0;
}
