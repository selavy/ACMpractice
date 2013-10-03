#include <stdio.h>
#include <stdlib.h>
#include <error.h>

int main (int argc, char ** argv)
{
  FILE * pIn;
  FILE * pOut;
  float b, w;

  pOut = stdout;
  if( argc == 1)
    {
      pIn = stdin;
    }
  else if (argc == 2)
    {
      pIn = fopen (argv[1], "r");
      if( pIn == NULL )
	{
	  perror ("fopen()");
	  exit (EXIT_FAILURE);
	}
    }
  else
    {
      fputs ("Usage: ./atm <input-file>\n", stderr);
    }

  fscanf( pIn, "%f %f\n", &w, &b );

  if( w > (b - .5))
    {
      fprintf( pOut, "%.2f\n", b);
    }
  else if( (int)w % 5 != 0 )
    {
      fprintf( pOut, "%.2f\n", b);
    }
  else
    {
      int a = 100 * b - 100 * w - 50;
      fprintf(pOut, "%d.%2d\n", a/100, a%100);
    }

  fclose(pIn);

  return 0;
}
