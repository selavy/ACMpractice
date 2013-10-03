#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint64_t myint;

#define MAX_STR 1024

void init_digits( short * digits )
{
  register unsigned short i = 0;
  for( ; i < 10; ++i )
    {
      digits[i] = 0;
    }
}

int main( int argc, char ** argv )
{
  /* vars */
  FILE *pIn, *pOut;
  char str[MAX_STR];
  myint v, t, z;
  short digits[10], solved, n;

  pOut = stdout;

  if( argc == 1 )
    {
      pIn = stdin;
    }
  else if( argc == 2)
    {
      pIn = fopen( argv[1], "r");
      if( NULL == pIn )
	{
	  perror("fopen()");
	  exit(EXIT_FAILURE);
	}
    }
  else
    {
      fputs("./multiple (optional) <input-file>", stderr);
      exit(EXIT_FAILURE);
    }

  while( !feof(pIn) )
  {
      init_digits(digits);
      solved = 0;
      n = 1;

      if( NULL == fgets(str, MAX_STR, pIn) )
	{
	  if( feof(pIn) )
	    {
	      break;
	    }
	  perror("formatting error");
	  exit(EXIT_FAILURE);
	}

      if( 1 != sscanf(str, "%" SCNu64 "\n", &v ) )
	{

	  perror("formatting error");
	  exit(EXIT_FAILURE);
	}

      while( !solved )
	{
	  z = n * v;
	  t = z;

	  while( t > 0 )
	    {
	      digits[ t % 10 ] |= 1;
	      t /= 10;
	    }

	  solved = digits[0] && digits[1] && digits[2] && digits[3] && digits[4] && digits[5] && digits[6] && digits[7] && digits[8] && digits[9];
	  // increment for next case
	  n++;
	}

      printf("%d\n", n-1);
      }

  fclose(pIn);
  fclose(pOut);

  exit(EXIT_SUCCESS);
}
