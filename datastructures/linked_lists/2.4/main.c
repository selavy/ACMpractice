/* add two numbers stored in linked lists in reverse order */
/* (3 -> 1 -> 5) + (5 -> 9 -> 2) => (8 -> 0 -> 8) */

#include<stdio.h>
#include<stdlib.h>

typedef struct llist llist;

struct llist
{
  llist * next;
  int v;
};

void init_list( llist ** myList, int value )
{
  *myList = (llist*) malloc( sizeof( llist ) );
  (**myList).next = NULL;
  (**myList).v = value;
}

void add_elem( llist ** myList, int elem )
{
  llist * node;

  if( *myList == NULL )
    init_list( myList, elem );
  else
    {
      node = *myList;
      while( (*node).next != NULL )
	node = (*node).next;

      (*node).next = (llist*) malloc( sizeof( llist ) );
      node = (*node).next;
      (*node).next = NULL;
      (*node).v = elem;
    }
}

void add_list( llist * a, llist * b, llist ** out )
{
  llist *a_curr, *b_curr;
  int a_val, b_val, out_val, carry;

  if( a == NULL || b == NULL )
    return;

  a_curr = a;
  b_curr = b;

  carry = 0;
  while( a_curr != NULL && b_curr != NULL )
    {
      a_val = 0;
      b_val = 0;
      out_val = 0;

      if( a_curr != NULL )
	a_val = (*a_curr).v;

      if( b_curr != NULL )
	b_val = (*b_curr).v;

      out_val = a_val + b_val + carry;

      if( out_val >= 10 )
	{
	  carry = 1;
	  out_val %= 10;
	}

      add_elem( out, out_val );

      if( a_curr != NULL )
	a_curr = (*a_curr).next;

      if( b_curr != NULL )
	b_curr = (*b_curr).next;
    }
}

void printer( llist* );

void print_list( llist * myList )
{
  printer( myList );
  printf("\n");
}

void printer( llist * myList )
{
  if( myList == NULL )
    return;
  else
    {
      printer( (*myList).next );
      printf("%d", (*myList).v );
    }
}

int main( int argc, char ** argv )
{
  llist *a, *b, *out;

  a = NULL;
  b = NULL;
  out = NULL;

  add_elem( &a, 3 );
  add_elem( &a, 1 );
  add_elem( &a, 5 );
  add_elem( &b, 5 );
  add_elem( &b, 9 );
  add_elem( &b, 2 );

  printf("a is: ");
  print_list( a );

  printf("b is: ");
  print_list( b );

  add_list(a,b,&out);
  printf("There sum is: ");
  print_list( out );

  return 0;
}
