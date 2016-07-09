#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

#define VECTOR_SIZE 100000

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
	point * squarePoints = new point[VECTOR_SIZE];

	// Unit Square (0,0) (0,1) (1,0) (1,1)
	point center;
	center.x = 0.5;
	center.y = 0.5;
	double radium  = 0.5;

	double pi = 0;
	for (int j = 0; j < 10; j++)
	{
		int M = 0;
		// 8 Threads
		#pragma omp sections
		{
			srand(time(NULL));
			#pragma omp section
			{
				for (int i = 0; i < VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}

			#pragma omp section
			{
				// srand(th_id);	
				for (int i = 1 * VECTOR_SIZE / 8; i < 2 * VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}

			#pragma omp section
			{
				// srand(th_id);	
				for (int i = 2 * VECTOR_SIZE / 8; i < 3 * VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}

			#pragma omp section
			{
				// srand(th_id);	
				for (int i = 3 * VECTOR_SIZE / 8; i < 4 * VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}

			#pragma omp section
			{
				// srand(th_id);	
				for (int i = 4 * VECTOR_SIZE / 8; i < 5 * VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}

			#pragma omp section
			{
				// srand(th_id);	
				for (int i = 5 * VECTOR_SIZE / 8; i < 6 * VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}

			#pragma omp section
			{
				// srand(th_id);	
				for (int i = 6 * VECTOR_SIZE / 8; i < 7 * VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}

			#pragma omp section
			{
				// srand(th_id);	
				for (int i = 7 * VECTOR_SIZE / 8; i < 8 * VECTOR_SIZE / 8; i++)
				{
					// Generating new random point inside the square
					point p;
					p.x = randomDouble();
					p.y = randomDouble();

					squarePoints[i] = p;
				}
			}
		}

		#pragma omp parallel for reduction(+:M)
		for (int i = 0; i < VECTOR_SIZE; i++)
		{
			if (isInsideCircle(squarePoints[i], radium, center))
			{
				M += 1;
			}
		}

		pi += 4 * (double) M/VECTOR_SIZE;
	}

	printf("%f\n", pi / 10);

	delete squarePoints;
}	