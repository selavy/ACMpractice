/* Delete node in middle of singly-linked list without access to previous node */

#include<stdio.h>
#include<stdlib.h>

typedef struct llist llist;

struct llist {
  llist * next;
  int v;
};

void init_llist( llist ** myList, int value )
{
  *myList = (llist*) malloc( sizeof( llist ) );
  (**myList).v = value;
  (**myList).next = NULL;
}

void add_elem( llist ** myList, int value )
{
  llist * l;
  if( *myList == NULL )
    init_llist( myList, value );
  else
    {
      l = *myList;

      while( (*l).next != NULL )
	l = (*l).next;

      (*l).next = (llist*) malloc( sizeof( llist ) );
      l = (*l).next;
      (*l).next = NULL;
      (*l).v = value;
    }
}

void print_list( llist * myList )
{
  int counter;
  counter = 0;
  while( myList != NULL )
    {
      printf("%d: %d\n", counter, (*myList).v );
      myList = (*myList).next;
      counter++;
    }
}

void remove_node( llist ** myList, int n )
{
  llist *node;
  int i;

  node = *myList;

  for( i = 0; i < n && node != NULL; ++i )
    {
      node = (*node).next;
    }

  if( node == NULL ) // n > sizeof list
    return;

  if( (*node).next != NULL )
    {
      (*node).v = (*(*node).next).v;
      (*node).next = (*(*node).next).next;
    }
  else
    {
      node = NULL;
    }
}

int main( int argc, char** argv )
{
  FILE * pFile;
  llist * myList;
  int in;

  if( argc != 2 )
    exit(EXIT_FAILURE);
  else
    {
      pFile = fopen( argv[1], "r" );
      if( NULL == pFile )
	{
	  exit(EXIT_FAILURE);
	}
    }

  myList = NULL;
  while( !feof( pFile ) && 1 == fscanf(pFile, "%d\n", &in ) )
    {
      add_elem( &myList, in );
    }
    printf("list is:\n");
    print_list(myList);

    printf("Which node would you like to remove? ");
    scanf("%d", &in);

    remove_node( &myList, in );

    printf("List is now:\n");
    print_list(myList);

  exit(EXIT_SUCCESS);
}
