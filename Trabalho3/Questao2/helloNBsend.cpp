#include "mpi.h"
#include <stdio.h>

using namespace std;

// Compile: mpic++ -std=c++11 helloNBsend.cpp -o helloNBsend.out
// Execute: mpirun -np <#PROCESS> ./helloNBsend.out

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
		partner = (size / 2) + rank;
	}
	else
	{
		partner = rank - (size / 2);
	}

	int vector[1];

	// Cada tarefa envia para seu parceiro uma mensagem com um inteiro: seu rank
	vector[0] = rank;
	
	MPI_Request requestSend, requestReceive;

	MPI_Isend(vector,1,MPI_INT,partner,rank,MPI_COMM_WORLD, &requestSend);
	printf("Envio. Tarefa %d enviou para %d \n", rank, partner);

	// Cada tarefa recebe do seu parceiro uma mensagem com um inteiro: taskid do parceiro
	MPI_Irecv(vector,1,MPI_INT,partner,partner,MPI_COMM_WORLD, &requestReceive);
	printf("Recebimento. Tarefa %d recebeu de %d \n", rank, partner);

	/* MPI_Wait, de modo que um rank nao finalize
	   sua execucacao antes de receber uma mensagem */
	MPI_Status status;
	MPI_Wait(&requestSend, &status);
	MPI_Wait(&requestReceive, &status);

	MPI_Finalize();
	
	return 0;
}