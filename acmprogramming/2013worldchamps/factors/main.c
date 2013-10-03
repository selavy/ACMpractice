#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 1024

int main( int argc, char ** argv )
{
  FILE * pIn;

  if( argc == 1 )
    {
      pIn = stdin;
    }
  else if( argc == 2 )
    {
      pIn = fopen( argv[1], "r" );
      if( pIn == NULL )
	{
	  perror("fopen()");
	  exit(EXIT_FAILURE);
	}
    }
  else
    {
      fputs("Formatting incorrect!", stderr);
      exit(EXIT_FAILURE);
    }

  while( NULL != fgets( line, MAX_STR, pIn ) && !feof(pIn) )
    {
      if(1 != sscanf( line, "%llu\n", &n ))
	{
	  exit(EXIT_SUCCESS);
	}

      for( i = 0; i*i <= n; ++i )
	{
	  if( 
    }
  exit(EXIT_SUCCESS);
} 
