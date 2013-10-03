#include <stdio.h>

unsigned long long ones( unsigned int i ) {
  switch( i )
    {
    case 1:
      return 3;
      break;
    case 2:
      return 3;
      break;
    case 3:
      return 5;
      break;
    case 4:
      return 4;
      break;
    case 5:
      return 4;
      break;
    case 6:
      return 3;
      break;
    case 7:
      return 5;
      break;
    case 8:
      return 5;
      break;
    case 9:
      return 4;
      break;
    default:
      return 0;
    }
}

unsigned long long teen( unsigned int i ) {
  switch( i )
    {
    case 11:
      return 6;
      break;
    case 12:
      return 6;
      break;
    case 13:
      return 8;
      break;
    case 14:
      return 8;
      break;
    case 15:
      return 7;
      break;
    case 16:
      return 7;
      break;
    case 17:
      return 9;
      break;
    case 18:
      return 8;
      break;
    case 19:
      return 8;
      break;
    default:
      return 0;
    }
}

unsigned long long tens( unsigned int i ) {
  switch( i )
    {
    case 2:
      return 6;
      break;
    case 3:
      return 6;
      break;
    case 4:
      return 5;
      break;
    case 5:
      return 5;
      break;
    case 6:
      return 5;
      break;
    case 7:
      return 7;
      break;
    case 8:
      return 6;
      break;
    case 9:
      return 6;
      break;
    default:
      return 0;
    }
}

unsigned long long t( unsigned int i )
{
  if( i == 10 )
    {
      return 3;
    }
  else if( i > 10 && i < 20 )
    {
      return teen( i );
    }
  else
    {
      return tens( i / 10 ) + ones( i % 10 );
    }
}

unsigned long long h( unsigned int i )
{
  unsigned long long n;
  n = 0;
  if( i != 0 )
    {
      n = ones( i / 100 ) + 7;
      if( i % 100 == 0 )
	{
	  return n;
	}
      else
	{
	  n += t( i % 100 ) + 3; 
	} 
      return n;
    }
  else
    {
      return n;
    }
}


unsigned long long letters( unsigned int i )
{
  if( i < 10 )
    {
      return ones( i );
    }
  else if( i < 100 )
    {
      return t( i );
    }
  else if( i < 1000 )
    {
      return h( i );
    }
  else
    {
      return 11;
    }
}

int main() {
  unsigned long long n;
  n = 0;
  unsigned int i;
  for( i = 1; i < 1001; ++i )
    {
      n += letters(i);
    }

  printf("%lli\n", n);
  /*
  printf("100 => %lli\n", letters(100) );
  printf("200 => %lli\n", letters(200) );
  printf("300 => %lli\n", letters(300) );
  for( i = 400; i < 1000; i += 100 )
    {
      printf("%d => %lli\n", i, letters(i) );
    }

  for( i = 111; i < 120; ++i )
    {
      printf("%d => %lli\n", i, letters(i) );
    }
  printf("124 => %lli\n", letters(124) );
  printf("324 => %lli\n", letters(324) );
  */
  /*
  n = 0;
  for( i = 1; i < 102; ++i )
    {
      n += letters(i);
    }

  printf("\n\n%lli\n", n);
  */
  printf("\n\n%lli\n", letters(101) );
  printf("\n\n%lli\n", t(1) );
  return 0;
}
  
