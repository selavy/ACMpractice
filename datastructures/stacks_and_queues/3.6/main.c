/* write a program to sort a stack in ascending order. Only functions that
   can be used are: push | pop | peek isEmpty */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_ELEM 512

typedef struct stack stack;
typedef struct queue queue;

struct stack
{
  int st[MAX_ELEM];
  int num_elems;
};

struct queue
{
  int qu[MAX_ELEM];
  int head, rear;
};

void init_queue( queue * q )
{
  memset( (*q).qu, 0, sizeof(int)*MAX_ELEM );
  (*q).head = 0;
  (*q).rear = 0;
}

int enqueue( queue * q, int value )
{
  (*q).qu[(*q).rear] = value;
  (*q).rear = ((*q).rear + 1) % MAX_ELEM;
  return 1;
}

int dequeue( queue * q )
{
  int retVal;
  if( (*q).rear == (*q).head )
    return -1;

  retVal = (*q).qu[(*q).head];
  (*q).head = ((*q).head + 1) % MAX_ELEM;
  return retVal;
}

int is_q_empty( queue q )
{
  return ( q.rear == q.head ) ? 1 : 0;
}

void init_stack( stack * s )
{
  memset( (*s).st, 0, sizeof(int)*MAX_ELEM );
  (*s).num_elems = 0;
}

int push( stack * s, int e )
{
  if( (*s).num_elems >= MAX_ELEM )
    return 0;

  (*s).st[(*s).num_elems] = e;
  return ++((*s).num_elems);
}

void pop( stack * s, int * value )
{
  if( (*s).num_elems == 0 )
    value = NULL;

  *value = (*s).st[--((*s).num_elems)];
}

void peek( stack * s, int * value )
{
  if( (*s).num_elems == 0 )
    value = NULL;

  *value = (*s).st[(*s).num_elems - 1];
}

int is_empty( stack s )
{
  return ( s.num_elems == 0 ) ? 1 : 0;
}

void print_stack( stack s )
{
  int value;
  while( !is_empty( s ) )
    {
      pop( &s, &value );
      printf("%d\n", value );
    }
}

void print_queue( queue q )
{
  while( !is_q_empty( q ) )
    {
      printf("%d\n", dequeue( &q ) );
    }
}

int main( int argc, char ** argv )
{
  stack s, t;
  int value, i, r, peek_value;

  srand( time( NULL ) );

  init_stack(&s);

  for( i = 0; i < 10; ++i )
    {
      r = rand() % 100;
      push(    &s, r );
    }

  print_stack( s );

  printf("\n\n");

  printf("sorting...\n");
  pop( &s, &value );
  push( &t, value );
  while( !is_empty( s ) )
    {
      pop( &s, &value );
      peek( &t, &peek_value );

      if( value <= peek_value )
	push( &t, value );
      else
	{
	  while( value > peek_value && !is_empty( t ) )
	    {
	      pop( &t, &peek_value );
	      push( &s, peek_value );
	      if( is_empty( t ) )
		break;
	      peek( &t, &peek_value );
	    }

	  push( &t, value );
	}
    }

  print_stack( t );

  return 0;
}
