#include "mpi.h" // Use o arquivo de inclusao MPI apropriado.
#include <stdio.h>
#include <iostream>

using namespace std;

// Compile: mpic++ -std=c++11 main.cpp -o main.out
// Execute: mpirun -np <#PROCESS> ./main.out

/* O que fazer:
	Use o arquivo de inclusao MPI apropriado. - OK
	Identifique a tarefa zero como a tarefa mestre. - ??????????????
	Inicialize o ambiente MPI. - OK
	Obtem o numero total de tarefas.
	Obtem a identificacao da tarefa (quem e).
	Imprime uma mensagem Ola, que inclui a identificacao da tarefa.
	A tarefa mestre deve imprimir o numero total de tarefas. - ????????
	Finaliza o ambiente MPI. - OK
*/

int main(int argc, char * argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);               // Inicialize o ambiente MPI.
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtem a identificacao da tarefa (quem e).
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtem a identificacao da tarefa (quem e).
	printf("Alo mundo!! Eu sou o processo %d de %d \n", rank, size); // Imprime uma mensagem Ola, que inclui a identificacao da tarefa.
	// cout << "Hello World" << endl;
	MPI_Finalize(); // Finaliza o ambiente MPI.
	return 0;
}