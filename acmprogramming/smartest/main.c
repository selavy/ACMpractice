#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 512
#define END 1024


typedef struct __node {
  struct __node * next;
  char name[MAX_STR];
} llist;

unsigned int list_has( llist * list, char str[MAX_STR] )
{
  unsigned int counter;
  counter = 0;
  while( list != NULL )
    {
      counter++;
      if( 0 == strncmp( (*list).name, str, MAX_STR ) )
	{
	  return counter;
	}
      else
	{
	  list = (*list).next;
	}
    }
  return 0;
}

void place( llist ** list, char str[MAX_STR], unsigned int loc )
{
  unsigned int counter;
  llist *node, *tmp;

  node = (llist*) malloc(sizeof(llist));
  (*node).next = NULL;
  strncpy((*node).name, str, MAX_STR);

  if( *list == NULL )
    {
      *list = node;
      return;
    }
  else
    {
      counter = 1;
      tmp = *list;
      for( ; counter < loc && (*tmp).next != NULL; ++counter )
	{
	  tmp = (*tmp).next; 
	}
      
      (*node).next = (*tmp).next;
      (*tmp).next = node;
    }
}



int main( int argc, char ** argv )
{
  FILE *pFile;
  char first[MAX_STR], second[MAX_STR], line[MAX_STR * 2];
  llist *list, *tmp;
  unsigned int first_posn, second_posn;

  if( argc == 1 )
    {
      pFile = stdin;
    }
  else if( argc == 2 )
    {
      pFile = fopen( argv[1], "r");
      if( NULL == pFile )
	{
	  perror("fopen()");
	  return -1;
	}
    }
  else
    {
      fputs("usage ./smart (optional) <input-file>\n", stderr);
      exit(EXIT_FAILURE);
    }

  list = NULL;
  fgets(line, MAX_STR * 2, pFile);
  while(  !feof( pFile ) )
    {
      if( 2 != sscanf( line, "%s %s\n", first, second ) )
	{
	  perror("sscanf()" );
	  return -1;
	}

      if( ( first_posn = list_has( list, first ) ) )
	{
	  if( ( second_posn = list_has( list, second ) ) )
	    {
	      if( first_posn > second_posn )
		{
		  continue;
		}
	      else
		{
		  place( &list, second, first_posn - 1 );
		}
	    }
	  else // second not in list
	    {
	      place( &list, second, first_posn );
	    }
	}
      else // first is not in list
	{
	  if( ( second_posn = list_has( list, second ) ) )
	    {
	      place( &list, first, second_posn - 1 );
	    }
	  else // first nor second in list
	    {
	      place( &list, first, END );
	      place( &list, second, END );
	    }
	}
      fgets(line, MAX_STR*2, pFile );
    }


  // print list
  while( list != NULL )
    {
      printf("%s\n", (*list).name);
      tmp = (*list).next;
      free(list);
      list = tmp;
    }

  return 0;
}
