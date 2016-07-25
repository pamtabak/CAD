#include <stdio.h>
#include <stdlib.h>
#include <iostream>


using namespace std;


void fill_vector(int vector[], int x, int size)
{
	for (int i = 0; i < size; i++)
    {
      vector[i] = x;
    }
}

int main(int argc, char * argv[])
{
  if (argc < 4){
    std::cout<<"Usage is:\n"<<argv[0]<<
      " <amount of numbers to generate>"<<
      " <number to fill array A>" <<
      " <numver to fill array B>" <<
      std::endl;

    return 0;

  }

  long N = atol(argv[1]);
  int J = atoi(argv[2]);
  int F = atoi(argv[3]);

  cout << "trying to allocate" << endl;

  int * a = new int[N];
  int * b = new int[N];
  double result = 0;

  cout << "trying to fill" << endl;

  fill_vector(a, J, N);
  fill_vector(b, F, N);
  cout << "allocated" << endl;


	for (int x = 0; x < N; x++)
    {
      result += a[x] * b[x];
    }
  std::cout << result << std::endl;

  delete[] a;
  delete[] b;

	return 0;
}
