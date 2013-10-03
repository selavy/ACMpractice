#include <stdio.h>

typedef unsigned long long ull;

ull arr[10000];

ull sum_divs( ull n )
{
  ull ret = 0;
  ull i;
  if( n > 10000 )
    {
      return ret;
    }
  if( arr[n] )
    {
      return arr[n];
    }
  else
    {
  for( i = 1; i < n; ++i )
    {
      if( n % i == 0 )
	{
	  ret += i;
	}
    }
  return ret;
    }
}

int main( int argc, char ** argv ) {
  ull i, t1, t2;
  ull ret = 0;
  for( i = 0; i < 10000; ++i )
    {
      arr[i] = 0;
    }
  
  for( i = 1; i < 10000; ++i )
    {
      t1 = sum_divs(i);
      t2 = sum_divs(t1);
      if( t2 == i && i != t1 )
	{
	  if( t2 < 10000 )
	    {
	  arr[t2] = i;
	  arr[i] = t2;
	    }
	  //printf("%llu => %llu => %llu\n", i, t1, t2 );
	  ret += i + t1;
	}
    }

  printf( "%llu\n", ret);
  
  //printf("%llu\n", sum_divs(284) );
  //printf("%llu\n", sum_divs(220) );
  return 0;
}
