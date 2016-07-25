/***********************

Jogo da Vida
Versão paralelizada

************************/

#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>      /* Arquivo de cabecalho mpi.h */

#define NI 700        /* tamanho dos array  */
#define NJ 700

#define NSTEPS 500    /* Numero de iteracoes */

int main(int argc, char *argv[])
{

  int i, j, n, im, ip, jm, jp, ni, nj, nsum, isum;
  float x;

  // Inicializando ambiente MPI
  MPI_Init(&argc, &argv);

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int **old, **new;

  // Regras:
  // Dividir as celulas entre os processos
  // Assumindo que o numero de processos e divisor do numero de linhas da matriz
  // dividir o dominio apenas na direcao j (horizontal)

  // Obs: A parte de alocacao tambem poderia ser paralelizada.
  if (rank == 0)
  {
    // alocacao
    ni  = NI + 2;  // celulas fantasmas nas bordas
    nj  = NJ + 2;
    old = malloc(ni*sizeof(int*));
    new = malloc(ni*sizeof(int*));

    for(i=0; i<ni; i++)
    {
      old[i] = malloc(nj*sizeof(int));
      new[i] = malloc(nj*sizeof(int));
    }

    // inicializando elementos, 0 ou 1
    for(i = 1; i <= NI; i++)
    {
      for(j = 1; j <= NJ; j++)
      {
        x = rand()/((float)RAND_MAX + 1);
        if(x < 0.5)
        {
        old[i][j] = 0;
        }
        else
        {
          old[i][j] = 1;
        }
      }
    }
  }

  // PRECISA ESPERAR ESSE PROCESSO TER TERMINADO!!
  // Não sei como, no outro caso não tivemos problemas com isso pq o broadcast demorava
  // Precisamos colocar aquela treco de Barrier, talvez. Mas acho que a solução não é essa

  // Identificando a tarefa e o numero total de tarefas
	printf("Ola! Eu sou o processo %d. O numero total de processos é %d \n", rank, size);

  char outfilename[255];
  sprintf(outfilename, "found.data_%d", rank);
  FILE* file = fopen(outfilename, "w");
  fprintf(file, "Sou a tarefa %d\n", rank);

  // Usamos column_type ja que estamos dividindo o dominio horizontalmente
  // Vamos utilizar essa variavel para enviar os dominios para cada tarefa 
  MPI_Datatype column_type;
  MPI_Type_vector(NI, 1, nj, MPI_INT, &column_type);
  MPI_Type_commit(&column_type);

  for(n = 0; n < NSTEPS; n++)
  {
    // Tarefa Mestre
    if (rank == 0)
    {
      MPI_Status status;

      for (int r = 0; r < size; r++)
      {
        // desconsiderando celulas mortas
        int nJrank = NJ / size;
        int jFrom  = (r * nJrank) + 1; 
        int jTo    = jFrom + nJrank - 1;

        // ????????
        MPI_Send(&old[1][jTo], 1, column_type, r, 0, MPI_COMM_WORLD);

        // enviar celulas mortas tambem.
        if (jTo == 0)
        {

        }
        else if (jTo == (NJ - 1))
        {

        }
        else
        {
          // ????????
          MPI_Send(&old[1][jTo - 1], 1, column_type, r, 0, MPI_COMM_WORLD);
          MPI_Send(&old[1][jTo + 1], 1, column_type, r, 0, MPI_COMM_WORLD);
        }
      }
    }

    /* condicoes de contorno para as esquinas do dominio */
    // old[0][0]       = old[NI][NJ];
    // old[0][NJ+1]    = old[NI][1];
    // old[NI+1][NJ+1] = old[1][1];
    // old[NI+1][0]    = old[1][NJ];

    // Recebe o que foi enviado e trabalha em cima disso
    // MPI_Receive();

    /* cond. contorno para faces direita/esquerda  */

  //   for(i = 1; i <= NI; i++)
  //   {
  //     old[i][0]    = old[i][NJ];
  //     old[i][NJ+1] = old[i][1];
  //   }

  //   /* cond. controno face inferior e superior */

  //   for(j = 1; j <= NJ; j++)
  //   {
  //     old[0][j]    = old[NI][j];
  //     old[NI+1][j] = old[1][j];
  //   }

  //   // Codigo Paralelo: Trocar elementos da interface paralela

  //   for(i = 1; i <= NI; i++)
  //   {
  //     for(j = 1; j <= NJ; j++)
  //     {
  //      im = i-1;
  //      ip = i+1;
  //      jm = j-1;
  //      jp = j+1;

  //      nsum = old[im][jp] + old[i][jp] + old[ip][jp]
  //           + old[im][j ]              + old[ip][j ]
  //           + old[im][jm] + old[i][jm] + old[ip][jm];

  //      switch(nsum)
  //       {
  //         case 3:
  //          new[i][j] = 1;
  //          break;
  //        case 2:
  //          new[i][j] = old[i][j];
  //          break;
  //         default:
  //          new[i][j] = 0;
  //      }
  //     }
  //   }

  //   /* copia estado  */
  //   for(i=1; i<=NI; i++)
  //   {
  //     for(j=1; j<=NJ; j++)
  //     {
  //      old[i][j] = new[i][j];
  //     }
  //   }
  }

  // /*  Conta o número de celulas  vivas no final */
  // isum = 0;
  // for(i = 1; i <= NI; i++)
  // {
  //   for(j = 1; j <= NJ; j++)
  //   {
  //     isum = isum + new[i][j];
  //   }
  // }
  // printf("\n# Celulas Vivas = %d\n", isum);


  for(i = 0; i < ni; i++)
  {
    free(old[i]);
    free(new[i]);
  }

  free(old);
  free(new);

  fclose(file);

  MPI_Finalize();

  return 0;
}
