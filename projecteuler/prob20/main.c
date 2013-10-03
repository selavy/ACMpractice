#include <stdio.h>
#include <string.h>


char c[] = "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000";
//char c[] = "3628800";

int main( int argc, char ** argv )
{
  unsigned int i;
  unsigned int v;
  unsigned int counter = 0;
  unsigned l = strlen( c );
  for( i = 0; i < l; ++i )
    {
      switch( c[i] )
	{
       case '1':
	  v = 1;
	  break;
	case '2':
	  v = 2;
	  break;
	case '3':
	  v = 3;
	  break;
	case '4':
	  v = 4;
	  break;
	case '5':
	  v = 5;
	  break;
	case '6':
	  v = 6;
	  break;
	case '7':
	  v = 7;
	  break;
	case '8':
	  v = 8;
	  break;
	case '9':
	  v = 9;
	  break;
	default:
	  v = 0;
	}
      //      printf("v = %d, counter = %d\n", v, counter);
      counter += v;
    }

  printf("%d\n", counter);
  return 0;
}
