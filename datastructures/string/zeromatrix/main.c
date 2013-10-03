#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 20
#define M 25

int matrix[M][N];

/* Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column is set to 0 */

void print_matrix()
{
  unsigned int i, j;
  for( i = 0; i < M; ++i )
    {
      for( j = 0; j < N; ++j )
	{
	  printf("%2u ", matrix[i][j] );
	}
      printf("\n");
    }
  printf("\n");
}

int main( int argc, char ** argv )
{
  unsigned int i, j;

  srand( time(NULL) );

  for( i = 0; i < M; ++i )
    {
      for( j = 0; j < N; ++j )
	{
	  matrix[i][j] = rand() % 100;
	}
    }

  print_matrix();

  for( i = 0; i < M; ++i )
    {
      for( j = 0; j < N; ++j )
	{
	  if( !matrix[i][j] )
	    {
	      memset( matrix[i], 0, sizeof(unsigned int) * N );
	      break;
	    }
	}
    }

  print_matrix();

  return 0;
}
