#include "mpi.h"
#include <stdio.h>

using namespace std;

// Compile: mpic++ -std=c++11 helloBsend.cpp -o helloBsend.out
// Execute: mpirun -np <#PROCESS> ./helloBsend.out

int main(int argc, char * argv[])
{
	MPI_Init(&argc, &argv);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	printf("Ola! Eu sou o processo %d. \n", rank);

	if (rank == 0)
	{
		printf("Numero total de tarefas = %d \n", size);
	}

	// Faca com que cada tarefa determine sua tarefa parceira para envio.
	int partner;
	if (rank < size / 2)
	{
		partner = size / 2 + rank;
	}
	else
	{
		partner = rank - size / 2;
	}

	int vector[1];

	// Cada tarefa envia para seu parceiro de uma mensagem com um inteiro: rank
	vector[0] = rank;
	MPI_Send(vector,1,MPI_INT,partner,rank,MPI_COMM_WORLD);
	printf("Envio. Tarefa %d tem parceria com %d \n", rank, partner);

	// Cada tarefa recebe do seu parceiro uma mensagem com um inteiro: taskid do parceiro
	MPI_Status status;
	MPI_Recv(vector,1,MPI_INT,partner,partner,MPI_COMM_WORLD, &status);
	printf("Recebimento. Tarefa %d tem parceria com %d \n", rank, partner);	

	MPI_Finalize();
	
	return 0;
}