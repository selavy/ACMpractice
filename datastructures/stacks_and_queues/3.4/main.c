#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned int n;

//#define __DEBUG__

typedef struct stack stk;
#define MAX_SIZE 128

int last_moved = -1;

struct stack
{
  int t;
  int arr[MAX_SIZE];
};

void init_stack( stk * s )
{
  (*s).t = 0;
  memset( (*s).arr, 0, sizeof((*s).arr) );
}

int is_empty( stk s )
{
  return ( s.t == 0 ) ? 1 : 0;
}

void push( stk * s, int value )
{
  if( ( (*s).t + 1 ) < MAX_SIZE )
    {
      (*s).arr[(*s).t] = value;
      (*s).t++;
    }
}

int pop( stk * s )
{
  if( is_empty( *s ) )
    return -1;

  return (*s).arr[--(*s).t];
}

int peek( stk * s )
{
  if( is_empty( *s ) )
    return -1;

  return (*s).arr[(*s).t - 1];
}

void print_stacks( stk f, stk s, stk t )
{
  printf("\nFirst stack: \n");
  if( is_empty( f ) )
    {
      printf("empty");
    }
  while( !is_empty( f ) )
    {
      printf("%d\n", pop( &f ) );
    }

  printf("\nSecond stack: \n");
  if( is_empty( s ) )
    {
      printf("empty\n");
    }
  while( !is_empty( s ) )
    {
      printf("%d\n", pop( &s ) );
    }

  printf("\nThird stack: \n");
  if( is_empty( t ) )
    {
      printf("empty\n");
    }
  while( !is_empty( t ) )
    {
      printf("%d\n", pop( &t ) );
    }
}

int can_move( stk * from, stk * to )
{
  int ifrom, ito;

  ifrom = peek( from );

  if( ifrom == last_moved )
    return 0;

  if( ifrom == -1 )
    return 0;

  ito = peek( to );



  if( ito == -1 )
    return 1;

  return ( ito > ifrom ) ? 1 : 0;
}

int move( stk * from, stk * to )
{
  if( can_move( from, to ) )
    {
      int ifrom;

      ifrom = pop( from );
      push( to, ifrom );
      return ifrom;
    }
  else
    {
      return -1;
    }
}


void p( stk f, stk s, stk t )
{
#ifdef __DEBUG__
  int first[3], second[3], third[3], i;
  int sz[3];

  for( i = 0; i < 3; ++i )
    sz[i] = 0;

  for( i = 0; i < 3; ++i )
    {
      first[i] = pop( &f );
      if( first[i] != -1 )
	sz[0]++;
    }

  for( i = 0; i < 3; ++i )
    {
      second[i] = pop( &s );
      if( second[i] != -1 )
        sz[1]++;
    }

  for( i = 0; i < 3; ++i )
    {
      third[i] = pop( &t );
      if( third[i] != -1 )
	sz[2]++;
    }

  for( i = 0; i < 3; ++i )
    {
      if( first[i] != -1 )
	printf("|%d | ", first[i]);
      else
	printf("|  | ");

      if( second[i] != -1 )
	printf("%d| ", second[i]);
      else
	printf(" | ");

      if( third[i] != -1 )
	printf("%d| ", third[i]);
      else
	printf(" | ");

      printf("\n");
    }
  printf("----------\n");
#endif
}

int main( int argc, char ** argv )
{
  stk f, s, t;
  int i;

  if( argc == 2 )
    n = atoi(argv[1]);
  else
    n = 3;

  init_stack( &f );
  init_stack( &s );
  init_stack( &t );

  for( i = n; i > 0; --i )
    push( &f, i );

#ifdef __DEBUG__
  printf("\n");
  p( f, s, t ); 
#endif 

  i = 0;
  while( ( !is_empty( f ) || !is_empty( s ) ) )
    {
      i++; // counter to keep from inf loops
      int moved;
      if( ( moved = move( &f, &s ) ) > 0 )
	{
#ifdef __DEBUG__
	  printf("moved %d first to second\n", moved );
#endif
	}
      else if( ( moved = move( &f, &t ) ) > 0 )
	{
#ifdef __DEBUG__
	  printf("moved %d first to third\n", moved );
#endif
	}
      else if( ( moved = move( &s, &t ) ) > 0 )
	{
#ifdef __DEBUG__
	  printf("moved %d second to third\n", moved );
#endif
	}
      else if( ( moved = move( &t, &f ) ) > 0 )
	{
#ifdef __DEBUG__
	  printf("moved %d third to first\n", moved );
#endif
	}
      else if( ( moved = move( &t, &s ) ) > 0 )
	{
#ifdef __DEBUG__
	  printf("moved %d third to second\n", moved );
#endif
	}
      else if( ( moved = move( &s, &f ) ) > 0 )
	{
#ifdef __DEBUG__
	  printf("moved %d second to first\n", moved );
#endif
	}
      else
	{
#ifdef __DEBUG__
	printf("NOP\n");
#endif
	}

      last_moved = moved;
      p( f, s, t );
    }
  

  print_stacks( f, s, t );

  printf("\n\nTook %d moves\n", i );
  return 0;
}
