/* Find the first loop in a circular list and print the earlier node */
#include<stdio.h>
#include<stdlib.h>

typedef struct llist llist;

struct llist
{
  llist * next;
  char c;
};

void init_llist( llist ** myList, char c )
{
  *myList = (llist*) malloc( sizeof( llist ) );
  (**myList).next = NULL;
  (**myList).c = c;
}

void add_elem( llist ** myList, char elem )
{
  llist * node;

  if( *myList == NULL )
    init_llist( myList, elem );
  else
    {
      node = *myList;
      while( (*node).next != NULL )
	node = (*node).next;

      (*node).next = (llist*) malloc( sizeof( llist ) );
      node = (*node).next;
      (*node).next = NULL;
      (*node).c = elem;
    }
}

void print_list( llist * myList )
{
  llist node;
  node = myList;
  while( node != NULL )
    {
      printf("%c ", (*node).c);
      node = (*node).next;
    }

  printf("\n");
}

int main( int argc, char ** argv )
{
  FILE * pFile;
  char c;
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
  while( !feof(pFile) && 1 == fscanf(pFile,"%c\n",&c) )
    {
      add_elem(myList);
    }

  printf("Current list:\n");
  print_list(myList);

  return 0;
}
