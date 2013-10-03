#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define __DEBUG__

#define STR_MAX 1024
#define OOR (STR_MAX)

int isSubstring( char * a, char * b )
{
  unsigned int i, size_a, size_b;
  char * str;

  size_a = strlen(a);
  size_b = strlen(b);

  str = b;
  
  if( size_a > size_b )
    return 0;

  for( i = 0; i < size_b; ++i )
    {
      if( 0 == strncmp( a, str, strlen( a ) ) )
	return 1;

      str++;
    }

  return 0;
}

int main(int argc, char ** argv )
{
  char str1[STR_MAX], str2[STR_MAX], holder[STR_MAX * 2];
  unsigned int size;

  if( argc != 3 )
    exit(EXIT_FAILURE);
  else
    {
      strncpy( str1, argv[1], (STR_MAX - 1) );
      str1[STR_MAX - 1] = '\0';

      strncpy( str2, argv[2], (STR_MAX - 1) );
      str2[STR_MAX - 1] = '\0';
    }

  size = strlen( str1 );

  if( size != strlen( str2 ) )
    goto NOT;

  if( 0 == strncmp( str1, str2, size ) )
    goto YES;

  strncpy( holder, str2, size );
  strncat( holder, str2, size );
  holder[STR_MAX*2 -1] = '\0';

  if( isSubstring( str1, holder ) )
    goto YES;
  else
    goto NOT;

 YES:
  printf("YES\n");
  goto END;
 NOT:
  printf("NOT\n");  
 END:
  exit(EXIT_SUCCESS);
}
