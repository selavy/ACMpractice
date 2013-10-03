#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* write an algorithm to remove all duplicate nodes from a linked list */

typedef struct llist llist;

struct llist {
  llist * next;
  int n;
};

void init_llist( llist ** myList, int value )
{
  llist * l;

  *myList = (llist*) malloc( sizeof( llist ) );
  l = *myList;

  (*l).next = NULL;
  (*l).n = value;
}

void add_elem( llist ** myList, int value )
{
  llist * t;

  if( *myList == NULL )
    init_llist( myList, value );
  else
    {
      t = *myList;
      while( (*t).next != NULL )
	t = (*t).next;

      (*t).next = (llist*) malloc( sizeof( llist ) );
      t = (*t).next;
      (*t).next = NULL;
      (*t).n = value;
    }
}

void remove_duplicates( llist ** myList )
{
  llist *f, *s, *p;

  f = *myList;

  while( f != NULL )
    {
      p = f;
      s = (*f).next;
      while( s != NULL )
	{
	  /* check if the the value of s is equal to the value of f */
	  if( (*f).n == (*s).n )
	    {
	      /* remove node */
	      (*p).next = (*s).next;
	      free(s);
	      s = (*p).next;
	      /* p remains the same */
	    }
	  else
	    {
	      p = s;
	      s = (*s).next;
	    }
	}
      f = (*f).next;
    }
}

void print_list( llist * myList )
{
  while( myList != NULL )
    {
      printf("%d\n", (*myList).n );
      myList = (*myList).next;
    }
  printf("\n");
}

int main( int argc, char ** argv )
{
  FILE * pFile;
  int in;
  llist * myList;

  if( argc != 2 )
    exit(EXIT_FAILURE);
  else
    {
      pFile = fopen( argv[1], "r" );
      if( pFile == NULL )
	exit(EXIT_FAILURE);
    }

  myList = NULL;
  while( !feof( pFile ) && 1 == fscanf(pFile, "%d\n", &in) )
    {
      add_elem( &myList, in );
    }

  printf("before...\n\n");
  print_list( myList );

  remove_duplicates( &myList );
  printf("after...\n\n");
  print_list( myList );

  return 0;
}
