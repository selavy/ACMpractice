#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_STR 256
#define MAX_SIZE 21
#define WALL UINT_MAX
#define INF (UINT_MAX - 1)
#define START 0
#define END (UINT_MAX -2)

typedef struct {
  unsigned int x;
  unsigned int y;
} point_t;

void print_graph( unsigned int ** graph, unsigned int x, unsigned int y )
{
  unsigned int i, j;
  for( i = 0; i < y; ++i )
    {
      for( j = 0; j < x; ++j )
	{
	  if( graph[i][j] == WALL )
	    {
	      printf("*");
	    }
	  else if(graph[i][j] == INF)
	    {
	      printf("-");
	    }
	  else if(graph[i][j] == START)
	    {
	      printf("M");
	    }
	  else if(graph[i][j] == END)
	    {
	      printf("C");
	    }
	  else
	    {
	      if( graph[i][j] >= 10 )
		{
		  printf("%u", (graph[i][j] % 10)+1);
		}
	      else
		{
		  printf("%u", graph[i][j]);
		}
	    }
	}
      printf("\n");
    }
}

void reconstruct( unsigned int ** graph, unsigned int ** visited, unsigned int x, unsigned int y, point_t end )
{
  /* vars */
  unsigned int i,j, value, tmp_value;
  point_t point;

  if( graph == NULL || visited == NULL )
    {
      perror("something went wrong!");
      exit(EXIT_FAILURE);
    }

  visited[7][7] = 0;
  /* init vars */
  value = INF;
  for( i = 0; i < y; ++i )
    {
      for( j = 0; j < x; ++j )
	{
	  visited[i][j] = 0;
	}
    }
  /* init point and visited array */
  point.x = end.x;
  point.y = end.y;
  visited[point.y][point.x] = 1;

  // get the value of the end point
  if( point.y > 1 && !visited[point.y-1][point.x] && graph[point.y-1][point.x] != WALL && graph[point.y-1][point.x] < value )
    {
      value = graph[point.y - 1][point.x];
    }
  if( point.y + 1 < y && !visited[point.y+1][point.x] && graph[point.y+1][point.x] != WALL && graph[point.y+1][point.x] < value )
    {
      value = graph[point.y+1][point.x];
    }
  if( point.x > 1 && !visited[point.y][point.x-1] && graph[point.y][point.x-1] != WALL && graph[point.y][point.x-1] < value )
    {
      value = graph[point.y][point.x-1];
    }
  if( point.x + 1 < x && !visited[point.y][point.x+1] && graph[point.y][point.x+1] != WALL && graph[point.y][point.x+1] < value )
    {
      value = graph[point.y][point.x+1];
    }
  if( value == INF )
    {
      perror("couldn\'t reconstruct the graph properly!");
      exit(EXIT_FAILURE);
    }

  fprintf(stderr, "shortest path is %u steps\n", value );

  /* get the end value */
  value++;

  while( value != 0 )
    {
      for( i = 0; i < y; ++i )
	{
	  for( j = 0; j < x; ++j )
	    {
	      if( graph[i][j] == value )
		{
		  //check those around it
		  tmp_value = 0;
		  if( i > 1 && graph[i-1][j] == (value + 1) )
		    {
		      tmp_value = 1;
		    }
		  else if( i + 1 < y && graph[i+1][j] == (value + 1) )
		    {
		      tmp_value = 1;
		    }
		  else if( j > 1 && graph[i][j-1] == (value +1 ) )
		    {
		      tmp_value = 1;
		    }
		  else if( j + 1 < x && graph[i][j+1] == (value + 1 ))
		    {
		      tmp_value = 1;
		    }

		  if( tmp_value )
		    {
		      visited[i][j] = 1;
		    }
		  else
		    {
		      graph[i][j] = INF;
		      visited[i][j] = 1;
		    }
		}
	      if( !visited[i][j] && graph[i][j] > value )
		{
		  graph[i][j] = INF;
		}
	    }
	}
      value--;
    }


  for( i = 0; i < y; ++i )
    {
      free( visited[i] );
    }
  free(visited);
}

void solve( unsigned int ** graph, unsigned int x, unsigned int y )
{
  unsigned int ** visited;
  unsigned int i, j, lowest;
  point_t curr, end;
  curr.x = 0;
  curr.y = 0;
  
  visited = (unsigned int**) malloc( sizeof(unsigned int*) * y );
  for( i = 0; i < y; ++i )
    {
      visited[i] = (unsigned int*) malloc(sizeof(unsigned int) * x );
      for( j = 0; j < x; ++j )
	{
	  visited[i][j] = 0;
	}
    }

  while( 1 )
    {
      // get the shortest distanct
      lowest = INF;
      for( i = 0; i < y; ++i )
	{
	  for( j = 0; j < x; ++j )
	    {
	      if( !visited[i][j] && graph[i][j] != WALL && graph[i][j] < lowest )
		{
		  lowest = graph[i][j];
		  curr.x = j;
		  curr.y = i;
		}
	    }
	}

      // check if done
      if( lowest == INF )
	break;

      if( lowest == END )
	{
	  visited[curr.y][curr.x] = 1;
	  end.x = curr.x;
	  end.y = curr.y;
	  continue;
	}

      // put back in these vars just bc it is easier
      i = curr.y;
      j = curr.x;
      visited[i][j] = 1;
      //check all neighbors
      // above
      if( i >= 1 && graph[i-1][j] != WALL && graph[i-1][j] != END && !visited[i-1][j] )
	{
	  graph[i-1][j] = graph[i][j] + 1;
	}

      // below
      if( i+1 < y && graph[i+1][j] != WALL && graph[i+1][j] != END && !visited[i+1][j] )
	{
	  graph[i+1][j] = graph[i][j] + 1;
	}

      // left
      if( j >= 1 && graph[i][j-1] != WALL && graph[i][j-1] != END && !visited[i][j-1] )
	{
	  graph[i][j-1] = graph[i][j] + 1;
	}

      // right
      if( j+1 < x && graph[i][j+1] != WALL && graph[i][j+1] != END && !visited[i][j+1] )
	{
	  graph[i][j+1] = graph[i][j] + 1;
	}
    }

  reconstruct( graph, visited, x, y, end );

  print_graph( graph, x, y );
}

int main( int argc, char ** argv )
{
  FILE * pIn;
  char line[256];
  unsigned int **graph, x, y, i, j, match;

  y = 0;
  if( argc == 1 )
    {
      pIn = stdin;
    }
  else if( argc == 2 )
    {
      pIn = fopen(argv[1], "r");
      if( NULL == pIn )
	{
	  perror("fopen()");
	  exit(EXIT_FAILURE);
	}
    }
  else
    {
      fputs("usage: ./maze (optional) <input-file>\n",stderr );
    }

  if( NULL == fgets( line, MAX_STR, pIn ) )
    {
      perror("fgets()");
      exit(EXIT_FAILURE);
    }

  if( 1 != sscanf(line,"%u\n", &y ) )
    {
      perror("dimension format incorrect!");
      exit(EXIT_FAILURE);
    }

    graph = (unsigned int**) malloc( sizeof(unsigned int*) * y );

    for( i = 0; i < y; ++i )
      {
	graph[i] = (unsigned int*) malloc( sizeof(unsigned int) * MAX_SIZE );
	fgets( line, MAX_SIZE, pIn );
	j = 0;
	x = 0;
	match = 0;
	while( line[j] != '\n' )
	  {
	    if( line[j] == '\"')
	      {
		if( match )
		  {
		    break;
		  }
		else
		  {
		    match = 1;
		  }
	      }
	    else
	      {
		if( line[j] == '*' )
		  {
		    graph[i][x] = WALL;
		  }
		else if( line[j] == 'M' )
		  {
		    graph[i][x] = START;
		  }
		else if( line[j] == 'C' )
		  {
		    graph[i][x] = END;
		  }
		else
		  {
		    graph[i][x] = INF;
		  }
		x++;
	      }
	    
	    j++;
	  }
      }

    solve( graph, x, y );

    free(graph);
    fclose(pIn);
    exit(EXIT_SUCCESS);
}
