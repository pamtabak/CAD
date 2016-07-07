#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

// N -> quantos pontos foram randomicamente escolhidos
// M -> numero de pontos que caiu dentro do circulo

typedef struct point
{
	double x;
	double y;
} point;

// returns random double number [0,1]
double randomDouble()
{
	return (double) (rand()) / (RAND_MAX);
}

bool isInsideCircle (point p, double radium, point center)
{
	// x^2 + y^2 <= r^2
	if ((pow(p.x - center.x, 2) + pow(p.y - center.y, 2)) <= pow(radium, 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(int argc, const char* argv[])
{
	int N = 0;
	int M = 0;

	// Criar Quadrado Unitario
	// Para facilitar, (0,0) (0,1) (1,0) (1,1)
	point center;
	center.x = 0.5;
	center.y = 0.5;
	double radium  = 0.5;

	// Gerar numeros aleatorios, sendo que cada thread gera numeros diferentes
	unsigned int th_id = omp_get_thread_num();
	#pragma omp parallel default(none) shared(N,M, radium, th_id, center)
	{
		srand(th_id);
		while (true)
		{
			// Generating new random point inside the square
			point p;
			p.x = randomDouble();
			p.y = randomDouble();
			// printf("%f,%f\n", p.x, p.y);

			#pragma omp critical
			{
				if (N == 10000)
				{
					printf("%f\n", 4 * (double) M/N);
				}
				N += 1;
			}

			// Checking if point is inside the circle
			if (isInsideCircle(p, radium, center))
			{
				#pragma omp atomic
				M += 1;
			}
		}
	}
}	