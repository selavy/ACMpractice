#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct tree tree;

#define MAX( x, y ) ( ( ( x ) > ( y ) ) ? ( x ) : ( y ) )
#define MIN( x, y ) ( ( ( x ) > ( y ) ) ? ( y ) : ( x ) )

struct tree
{
  tree * left;
  tree * right;
  int value;
};

void init_tree( tree ** t, int v )
{
  *t = (tree*) malloc( sizeof( tree ) );
  (**t).left = NULL;
  (**t).right = NULL;
  (**t).value = v;
}

void add( tree ** tr, int v )
{
  tree * t;

  if( *tr == NULL )
    init_tree( tr, v );

  else
    {
      t = *tr;
      while( 1 )
	{
	  if( v < (*t).value )
	    {
	      if( (*t).left == NULL )
		{
		  (*t).left = (tree*) malloc( sizeof( tree ) );
		  t = (*t).left;
		  break;
		}
	      else
		t = (*t).left;
	    }
	  else
	    {
	      if( (*t).right == NULL )
		{
		  (*t).right = (tree*) malloc( sizeof( tree ) );
		  t = (*t).right;
		  break;
		}
	      else
		t = (*t).right;
	    }
	}

      (*t).left = NULL;
      (*t).right = NULL;
      (*t).value = v;
    }
}

void inorder( tree * t )
{
  if( t == NULL )
    return;

  inorder( (*t).left );
  printf("%d\n", (*t).value );
  inorder( (*t).right );
}

int max_height( tree * t )
{
  if( t == NULL )
    return 0;
  else
    return 1 + MAX( max_height( (*t).left ), max_height( (*t).right ) );
}

int min_height( tree * t )
{
  if( t == NULL )
    return 0;
  else
    return 1 + MIN( min_height( (*t).left ), min_height( (*t).right ) );
}

void is_balanced( tree * t )
{
  int m, mm;
  m = max_height( t );
  mm = min_height( t );
  printf("m = %d, mm = %d\n", m, mm);
  if( m - mm <= 1 )
    printf("balanced\n");
  else
    printf("unbalanced\n");
}

int main( int argc, char ** argv )
{
  int i;
  tree * t;

  srand( time(NULL) );

  t = NULL;
  for( i = 0; i < 4; ++i )
    {
      add( &t, rand() % 500 );
    }

  inorder( t );
  printf("\n");
  is_balanced( t );
  return 0;
}
