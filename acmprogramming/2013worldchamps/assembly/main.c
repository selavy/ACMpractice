#include <stdio.h>
#include <stdlib.h>

/*************************************/
/*      DEFINES                      */
/*************************************/
#define MAX_STR 512
#define SIZE 52 /* == 26 * 2 */
#define NO_CONN SIZE

/* just to see some output useful for debugging */
/* or understanding the program, but will       */
/* obviously break the makefile because the     */
/* diffs will fail.                             */
//#define __DEBUG__

/*************************************/
/*      MACROS                       */
/*************************************/
/* 'A' = 65 */
#define POSITIVE( x ) ( x - 65 )
/* #define NEGATIVE( x ) ( x - 65 + 26 ) */
#define NEGATIVE( x ) ( x - 39 )

/*************************************/
/*      TYPES                        */
/*************************************/
typedef char node[8];

/*************************************/
/*      GLOBALS                      */
/*************************************/
uint num_blocks;
FILE * pFile;
char graph[SIZE][SIZE];

/*************************************/
/*      FUNCTION PROTOS              */
/*************************************/
void get_num_blocks();
int get_block(node*);
uint to_index(char*);
int traverse();
void print_graph();
int cycle(uint,uint,uint);
/************************************/
/*      WHERE THE MAGIC HAPPENS     */
/************************************/
int
main( int argc, char ** argv )
{
  /* Vars */
  uint i, j, k;
  node block;

  /* check to make sure an input file was supplied      */
  /* get the number of blocks (the first line of input) */
  /* I am just assuming that the input will always be   */
  /* correct since this is for a competition            */
  if( argc == 2)
    get_num_blocks(argv[1]);
  else
    exit(EXIT_FAILURE);

  /* Initialize the graph and cycles arrays */
  /* The graph array is an incidence matrix */
  /* if graph(i,j) is true, then there is a */
  /* directed edge from i -> j              */
  for( i = 0; i < SIZE; ++i )
    {
      for( j = 0; j < SIZE; ++j )
	{
	  graph[i][j] = NO_CONN;
	}
    }
  
  /* Get the input blocks */
  for( i = 0; i < num_blocks; ++i )
    {
      /* for each block... */
      if( get_block( &block ) > 2 )
	{
	  /* if the block has more than 2 '00' terms then just skip it */
	  /* if the block has 3 or 4 sides with '00' terms then it     */
	  /* cannot connect to anything so it doesn't matter           */
	  continue;
	}
      /* else // block has less than 2 zeros                           */

      /* if a block matches itself, then the structure is unbounded    */
      /* We wouldn't have to do this, but it is a simple enough check  */
      /* and as n -> 40,000 it can save a lot of time                  */
      for( k = 0; k < 4; ++k )
	{
	  for( j = 0; j < 4; ++j )
	    {
	      if( block[k*2] == block[j*2] && block[k*2+1] != block[j*2+1] )
		  goto unbounded;
	    }
	}

      /* else // block does not match itself */
      /* add links to the graph              */
      for( j = 0; j < 4; ++j )
	{
	  /* For each side... */

	  /* assume correct formatting so only need to test first block for if 0 */
	  if( block[j*2] == '0' )
	    {
	      /* no links can be added */
	      continue;
	    }
	  else
	    {
	      for( k = 0; k < 4; ++k )
		{
		  /* for every other side on the block... */
		  if( j == k ) /* same side we are already on, so continue */
		    continue;
		  else if( block[k*2] == '0' ) /* side is 00 so continue */
		    continue;
		  /* else add link */
		  /* The basic idea for the links is, add a directed edge */
		  /* between the opposite of that side (i.d. opposite of  */
		  /* P- is P+) to each of the other sides on the block.   */
		  /* This is because if you can connect to the current    */
		  /* side of the block (i.d. block[j*2]) then you will    */
		  /* connect with the opposite of this block, and it will */
		  /* connect you to any of the other sides of the current */
		  /* block.                                               */
		  /* The problem is actually pretty nice since you can    */
		  /* rotate and reflect, the geometry of the block doesnt */
		  /* actually matter.                                     */
		  if( block[j*2+1] == '+' )
		    graph[ NEGATIVE( block[j*2] ) ][ to_index( &block[k*2] ) ] = 1;
		  /* else the block is negative */
		  else
		    graph[ POSITIVE( block[j*2] ) ][ to_index( &block[k*2] ) ] = 1;
		}
	    }
	}

      /* turn on __DEBUG__ if you want to see the graph */
      print_graph();
    }

  /* graph is all set up, just check for cycles */
  if( traverse() )
    goto unbounded; /* U mad bro? */

  /* if we made it here then it is a bounded structure */
      printf("bounded\n");
      exit(EXIT_SUCCESS);

    unbounded:
      printf("unbounded\n");
      exit(EXIT_SUCCESS);
} /**~ end main ~**/

/***********************************/
/*      FUNCTION DEFTNS            */
/***********************************/

/* open the file and get the number of blocks */
void
get_num_blocks( char * file_name ) {
  /* Vars */
  char line[MAX_STR];
  /*------*/

  pFile = fopen( file_name, "r" );
  if( pFile == NULL )
    exit(EXIT_FAILURE);

  if( NULL == fgets( line, MAX_STR, pFile ) )
    exit(EXIT_FAILURE);

  if( 1 != sscanf( line, "%u\n", &num_blocks ) )
    exit(EXIT_FAILURE);

  return;
} /**~ end get_num_blocks ~**/

/* get a block from file */
/* assumes that pFile is open and that formatting is correct :P */
/* This returns the number of 00 sides on the block             */
int
get_block( node * b ) {
  /* Vars */
  char c;
  uint count, i; 
  /*-----*/

  count = 0;
  for( i = 0; i < 4; ++i )
    {
      c = fgetc( pFile );
      count += ( c == '0' ) ? 1 : 0;
      (*b)[2*i] = c;
      (*b)[2*i+1] = fgetc( pFile );
    }

  /* get the space in between each block */
  fgetc( pFile );
  return count;
} /**~ end add_block ~**/

/* convert a side (e.g. "A+) to its index in the graph */
/* assume that b points to at least 2 chars            */
uint
to_index( char * b )
{
  if( b[1] == '+' )
    return POSITIVE( *b );
  else
    return NEGATIVE( *b );
} /**~ end to_index ~**/

/* print the graph, just for debugging */
/* uncomment the #define DEBUG line to */
/* see the output                      */
void
print_graph() {
#ifdef __DEBUG__
  /* Vars */
  uint i,j;
  /*------*/

  printf("\n\nDEBUG: printing the graph\n");
  for( i = 0; i < SIZE; ++i )
    {
      printf("%2u: ", i);
      for( j = 0; j < SIZE; ++j )
	{
	  if( graph[i][j] == NO_CONN )
	    printf("*");
	  else
	    printf("%d", (int) graph[i][j] );
	}
      printf("\n");
    }
  printf("\n\n");
#endif
} /**~ end print_graph() ~**/

/* traverse the graph, checking for cycles   */
/* I'm sure this isn't the fastest algorithm */
/* but since we only have to check a graph   */
/* with 26*2 nodes, it isn't really a big    */
/* maybe you can find a better algorithm?    */
int
traverse() {
  /* Vars */
  uint i, j;
  /*------*/

  /* For each row in the graph... */
  for( i = 0; i < SIZE; ++i )
    {
      for( j = 0; j < SIZE; ++j )
	{
	  /* For each column...             */
	  /* Is there a directed edge i->j? */
	  if( graph[i][j] != NO_CONN )
	    {
	      /* Try to follow this edge */
	      if( cycle( j, i, 0 ) )
		return 1;
	    }
	}
    }  
  return 0;
} /**~ end traverse ~**/

/* Check for cycles                          */
/* This function has 2 checks:               */
/* First it checks if the cycle length is    */
/* greater than SIZE because if it is, then  */
/* it has to repeat a node.The second check  */
/* is if the starting node has been repeated */
int
cycle( uint to, uint start, uint length )
{
  uint i;

  if( length > SIZE )
    return 1;
  if( to == start )
    return 1;

  for( i = 0; i < SIZE; ++i )
    {
      if( graph[to][i] != NO_CONN )
	{
	  if( cycle( i, start, length + 1 ) )
	    return 1;
	}
    }

  return 0;
} /**~ end cycle ~**/
