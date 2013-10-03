#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float real;
  float comp;
} complex;

int main( int argc, char ** argv )
{
  FILE * pInput;
  
    if( argc == 2 )
    {
      pInput = fopen (argv[1], "r");
      if (NULL == pInput)
	{
	  perror("fopen()");
	  return -1;
	}
    }
  else if (argc ==1)
    {
      pInput = stdin;
    }
  else
    {
      perror ("Usage: ./complex (optional)<input-file>");
      return -1;
    }

  complex a, b;
  char op;

  while( EOF != fscanf(pInput,"\(%f,%f) %c \(%f,%f)\n", &a.real, &a.comp, &op, &b.real, &b.comp) )
    {
      if( op == '+' )
	{
	  printf("(%g,%g)\n", a.real + b.real, a.comp + b.comp );
	}
      else if( op == '-')
	{
	  printf("(%g,%g)\n", a.real - b.real, a.comp - b.comp );
	}
      else if (op=='*')
	{
	  printf("(%g,%g)\n", a.real*b.real - a.comp*b.comp, a.real*b.comp + a.comp*b.real);
	}
      else if (op == '/')
	{
	  printf("(%g,%g)\n", (a.real*b.real+a.comp*b.comp)/(b.real*b.real + b.comp*b.comp), (a.comp*b.real-a.real*b.comp)/(b.real*b.real + b.comp*b.comp));
	}
      else
	{
	  printf("wrong\n");
	}
    }
  return 0;
}
