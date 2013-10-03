#include <stdio.h>
#include <time.h>

#define MAX 28123
#define TRUE 1
#define FALSE 0

unsigned long divs[MAX];
unsigned long abundants[MAX];
char gg[MAX];

int main( int argc, char** argv )
{
  //  clock_t begin, end;
  //double time_spent;

  //begin = clock();

  unsigned long i, j;
  unsigned long long counter = 2;
  unsigned long long tmp = 1;
  for( i = 1; i <= MAX; ++i )
    {
      counter = 2;
      tmp = counter * i;
      while( tmp <= MAX )
	{
	  divs[tmp-1] += i;
	  counter++;
	  tmp = counter * i;
	}

      // initialize my arrays since already have loop [0..MAX-1]
      gg[i-1] = FALSE;
      abundants[i-1] = 0;
    }

  // fill in 1, since it is weird
  divs[0] = 1;

  for( i = 0; i < MAX; ++i )
    {
      //      printf("%ld => %ld\n", i+1, divs[i] );
      if( i + 1 < divs[i] )
	{
	  abundants[i] = divs[i];
      	}
    }

  for( i = 0; i < MAX; ++i )
    {
      if( !abundants[i] )
	continue;
      if( abundants[i] )
	{
	  for( j = 0; j < MAX; ++j )
	    {
	      if( abundants[j] )
		{
		  tmp = (i + 1) + j;
		  if( tmp < MAX )
		    {
		      gg[tmp] = TRUE;
		    }
		}
	    }
	}
    }

  unsigned long long sum = 0;
  for( i = 0; i < MAX; ++i )
    {
      if( !gg[i] )
	{
	  sum += ( i + 1 );
	}
    }

  printf("%lld\n", sum);

  //end = clock();
  //  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  //printf("time spent: %lf seconds\n", time_spent);
  return 0;
}
