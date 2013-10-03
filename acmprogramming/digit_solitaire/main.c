#include<stdio.h>
#include<stdlib.h>

#define MAX_STR 256

void solve( unsigned int number )
{
  unsigned int count, next;

  while( 1 )
    {
      printf("%u", number);
      next = 1;
      count = 1;
      while( number / 10 != 0 )
	{
	  next *= number % 10;
	  count++;
	  number /= 10;
	}

      next *= number % 10;

      if( count == 1 )
	break;
      else
	{
	  printf(" ");
	  number = next;
	}
    }
  printf("\n");
}

int main (int argc, char ** argv)
{
  /* variables */
  FILE *pIn;
  unsigned int number;
  char line[MAX_STR];

  if (argc == 1)
    {
      pIn = stdin;
    }
  else if (argc == 2)
    {
      pIn = fopen (argv[1],"r");
      if (NULL == pIn)
	{
	  perror ("fopen()");
	  exit (EXIT_FAILURE);
	}
    }
  else
    {
      fputs("usage: ./solitaire (optional) <input-file>\n", stderr);
      exit(EXIT_FAILURE);
    }

  if (NULL == fgets (line, MAX_STR, pIn))
    {
      perror("fgets()");
      exit (EXIT_FAILURE);
    }

  if (1 != sscanf( line, "%u\n", &number ))
    {
      perror("sscanf()");
      exit(EXIT_FAILURE);
    }

    while( number != 0 )
      {
	solve( number );
	if (NULL == fgets(line, MAX_STR, pIn) )
	  {
	    perror("sscanf()");
	    exit(EXIT_FAILURE);
	  }

	if(1 != sscanf(line,"%u\n",&number))
	  {
            perror("sscanf()");
	    exit(EXIT_FAILURE);
	  }
      }

  fclose(pIn);
  exit(EXIT_SUCCESS);
}
