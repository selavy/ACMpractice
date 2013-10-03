#include <stdio.h>
#include <stdlib.h>

#define LINES 100
#define SIZE ( LINES * ( LINES + 1 ) / 2 )

unsigned int highest = 0;

unsigned int get_row( unsigned int node )
{
  if( node == 0 )
    return 0;
  unsigned int i, limit;
  limit = 3;
  for( i = 1; i < LINES; ++i )
    {
        if( node < limit )
	  return i;
	limit += (i + 2);
    }
  return LINES;
}

unsigned int get_left( unsigned int node )
{
  return node + get_row( node ) + 1;
}

unsigned int get_right( unsigned int node )
{
  return get_left( node ) + 1;
}

void print_triangle( unsigned int g[SIZE], unsigned int r )
{
  unsigned int i, j, counter;
  counter = 0;
  for( i = 0; i <= r; ++i )
    {
      printf("row #%d ", i);
      for( j = 0; j <= i; ++j )
	{
	  printf("%d ", g[counter]);
	  counter++;
	}
      printf("\n");
    }

  printf("\n\n");
}

void solve( unsigned int g[SIZE] )
{
  unsigned int i, j, b, index, l, r;
  for( i = ( LINES - 2 ); i >= 1; --i )
    {
      for( j = 0; j <= i; ++j )
	{
	  index = i * (i + 1) / 2;
	  l = g[ get_left( index + j ) ];
	  r = g[ get_right( index + j ) ];
	  b = ( l > r ) ? l : r;
	  g[ index + j ] += b;
	}

      //print_triangle( g, i + 1 );
    }

  // add the last two
  highest = g[1] > g[2] ? g[1] : g[2];
  highest += g[0];
}

int main( int argc, char ** argv )
{
  FILE * pFile;

  if( argc != 2 )
      return 1;

  pFile = fopen( argv[1], "r" );
  if( pFile == NULL )
    return 1;

  unsigned int graph[SIZE];
  unsigned int i, j, counter;

  counter = 0;
  for( i = 1; i <= LINES; ++i )
    {
      for( j = 0; j < i; ++j )
	{
	  fscanf(pFile, "%ud", &graph[counter]);
	  counter++;
	}
      fscanf(pFile, "\n");
    }

  solve( graph );
  printf("%u\n", highest );
  return 0;
}
