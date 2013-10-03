#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 256

int main( int argc, char ** argv )
{
  /* vars */
  FILE * pIn;
  char line[MAX_STR];
  unsigned long long n, i, g, e, a, b, c, d, f, h, j;

  if( argc == 1 )
    {
      pIn = stdin;
    }
  else if( argc == 2 )
    {
      pIn = fopen(argv[1], "r");
      if( pIn == NULL )
	{
	  perror("fopen()");
	  exit(EXIT_FAILURE);
	}
    }
  else
    {
      fputs("Usage: ./goodevil (optional) <input-file>\n", stderr);
    }

  if( NULL == fgets(line,MAX_STR,pIn) )
    {
      perror("input incorrect");
      exit(EXIT_FAILURE);
    }

  if( 1 != sscanf(line,"%llu\n",&n) )
    {
      perror("input incorrect");
      exit(EXIT_FAILURE);
    }

  for( i = 1; i <= n; ++i )
    {
      g = e = 0;
      printf( "Battle %llu: ", i );

      if( NULL == fgets( line, MAX_STR, pIn ) )
	{
	  perror("incorrect format");
	  exit(EXIT_FAILURE);
	}

      if( 6 != sscanf(line, "%llu %llu %llu %llu %lld %llu\n", &a, &b, &c, &d, &f, &h ) )
	{
	  perror("incorrect format");
	  exit(EXIT_FAILURE);
	}

	g = a + b*2 + c*3 + d*3 + f*4 + h*10;

	if( NULL == fgets( line, MAX_STR, pIn ) )
	  {
	    perror("incorrect format");
	    exit(EXIT_FAILURE);
	  }

	if( 7 != sscanf(line, "%llu %llu %llu %llu %llu %llu %llu\n", &a, &b, &c, &d, &f, &h, &j ) )
	  {
	    perror("incorrect format");
	    exit(EXIT_FAILURE);
	  }

	e = a + 2*b + 2*c +2*d + 3*f + 5*h + 11*j;

	if( e > g )
	  {
	    printf("Evil eradicates all trace of Good\n");
	  }
	else if( g > e )
	  {
	    printf("Good triumphs over Evil\n");
	  }
	else
	  {
	    printf("No victor on this battle field\n");
	  }
    }

  exit(EXIT_SUCCESS);
}
