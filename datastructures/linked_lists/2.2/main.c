#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct llist llist;

struct llist
{
  llist * next;
  int v;
};

void init_list( llist ** myList, int value )
{
  llist * l;
  *myList = (llist*) malloc( sizeof( llist ) );
  l = *myList;

  (*l).next = NULL;
  (*l).v = value;
}

void add_elem( llist ** myList, int value )
{
  llist * t;

  if( *myList == NULL )
    init_list( myList, value );
  else
    {
      t = *myList;
      while( (*t).next != NULL )
	t = (*t).next;

      (*t).next = (llist*) malloc( sizeof( llist ) );
      t = (*t).next;

      (*t).next = NULL;
      (*t).v = value;
    }
}

int find_nth_from_end( llist * myList, int n )
{
  llist *f, *s;
  unsigned int i;

  if( n < 0 )
    return -1;

  f = myList;

  for( i = 0; i < n; ++i )
    {
      if( f == NULL )
	return -1;
      else
	f = (*f).next;
    }

  s = myList;

  while( (*f).next != NULL )
    {
      f = (*f).next;
      s = (*s).next;
    }

  return (*s).v;
}

int main( int argc, char ** argv )
{
  FILE * pFile;
  int n;
  llist * myList;

  if( argc != 2 )
    exit(EXIT_FAILURE);
  else
    {
      pFile = fopen( argv[1], "r" );
      if( NULL == pFile )
	exit(EXIT_FAILURE);
    }

  myList = NULL;
  while( !feof(pFile) && 1 == fscanf( pFile, "%d\n", &n ) )
    {
      add_elem( &myList, n );
    }

  fclose( pFile );

  printf("What is n? ");
  scanf("%d", &n );

  printf("%dth element from the end is: %d", n, find_nth_from_end( myList, n ) );

  exit(EXIT_SUCCESS);
}
