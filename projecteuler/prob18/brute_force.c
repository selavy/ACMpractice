#include <stdio.h>
#include <stdlib.h>

unsigned int highest = 0;

unsigned int get_row( unsigned int node )
{
  if( node == 0 )
    return 0;
  else if( node < 3 )
    return 1;
  else if( node < 6 )
    return 2;
  else if( node < 10 )
    return 3;
  else if( node < 15 )
    return 4;
  else if( node < 21 )
    return 5;
  else if( node < 28 )
    return 6;
  else if( node < 36 )
    return 7;
  else if( node < 45 )
    return 8;
  else if( node < 55 )
    return 9;
  else if( node < 66 )
    return 10;
  else if( node < 78 )
    return 11;
  else if( node < 91 )
    return 12;
  else if( node < 105 )
    return 13;
  else if( node < 120 )
    return 14;
  else
    return 15;
}

unsigned int get_row_a( unsigned int node )
{
  return get_row( node ) + 1;
}

unsigned int get_left( unsigned int node )
{
  return node + get_row( node ) + 1;
}

unsigned int get_right( unsigned int node )
{
  return get_left( node ) + 1;
}

void solve( unsigned int g[225], unsigned int i, unsigned int h )
{
  if( get_row( i ) == 14 )
    {
      if( g[i] + h > highest )
	{
	  highest = g[i] + h;
	}
    }
  else
    {
      solve( g, get_left( i ), h + g[i] );
      solve( g, get_right( i ), h + g[i] );
    }
}

int main( int argc, char ** argv )
{
  FILE * pFile;

  if( argc != 2 )
      return 1;

  pFile = fopen( argv[1], "r" );
  if( pFile == NULL )
    return 1;

  unsigned int graph[120];
  unsigned int i, j, counter;

  counter = 0;
  for( i = 1; i < 16; ++i )
    {
      for( j = 0; j < i; ++j )
	{
	  fscanf(pFile, "%ud", &graph[counter]);
	  counter++;
	}
      fscanf(pFile, "\n");
    }

  solve( graph, 0, 0 );
  printf("%u\n", highest );
  return 0;
}
