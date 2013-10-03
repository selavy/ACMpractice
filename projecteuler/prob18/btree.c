#include <stdio.h>
#include <stdlib.h>

typedef struct __btree
{
  struct __btree * left;
  struct __btree * right;
  int * data;
} btree;

void add_to_tree( btree ** bt, int data ) {
  if( (*bt) == NULL )
    {
      // make new btree
      (*bt) = (btree*) malloc( sizeof( btree ) );
      (*(*bt)).left = NULL;
      (*(*bt)).right = NULL;
      (*(*bt)).data = (int*) malloc( sizeof(int) );
      (*(*(*bt)).data) = data;
    }
  else
    {
      if( data < (*(*(*bt)).data) )
	{
	  add_to_tree( &((*(*bt)).left), data );
	}
      else
	{
	  add_to_tree( &((*(*bt)).right), data );
	}
    }
}

void print_tree( btree * bt )
{
  if( bt == NULL )
    return;
  else
    {
      print_tree( (*bt).left );
      printf("%d\n", (*(*bt).data) );
      print_tree( (*bt).right );
    }
}

void delete_tree( btree * bt )
{
  if( bt == NULL )
    return;
  else
    {
      delete_tree( (*bt).left );
      delete_tree( (*bt).right );
      free( (*bt).data );
      free( bt );
    }
}

int main( int argc, char** argv ) {
  btree * b;
  b = NULL;
  //add_to_tree( &b, 1 );

  FILE * pFile;

  if( argc != 2 )
    {
      fputs("usage: ./prob18 <inputfile>\n", stderr );
    }
  else
    {
      pFile = fopen( argv[1], "r" );
    }

  if( pFile == NULL )
    {
      fputs("unable to open input file!\n", stderr );
    }

  while( !feof )
    {

  delete_tree( b );
  return 0;
}
