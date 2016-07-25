#include "mpi.h" // Use o arquivo de inclusao MPI apropriado.
#include <stdio.h>

using namespace std;

// Compile: mpic++ -std=c++11 main.cpp -o main.out
// Execute: mpirun -np <#PROCESS> ./main.out

int main(int argc, char * argv[])
{
	
	// Inicialize o ambiente MPI.
	MPI_Init(&argc, &argv);

	// Obtem o numero total de tarefas.
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Obtem a identificacao da tarefa (quem e).
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Imprime uma mensagem Ola, que inclui a identificacao da tarefa.
	printf("Ola! Eu sou o processo %d. \n", rank);

	// A tarefa mestre deve imprimir o numero total de tarefas.
	if (rank == 0)
	{
		printf("Numero total de tarefas = %d \n", size);
	}

	// Finaliza o ambiente MPI.
	MPI_Finalize();
	
	return 0;
}