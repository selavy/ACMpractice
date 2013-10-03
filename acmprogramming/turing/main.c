#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 256
#define READ_RULE 1
#define READ_START 2
#define EXECUTE 3
#define END 4
#define READ_TAPE 5
#define CLUSTER_SIZE 50

typedef struct {
  unsigned int state;
  char symbol;
  char action;
  unsigned int next_state;
} inst;

typedef struct __snode {
  inst * rule;
  struct __snode * next;
} llist;

typedef struct __lnode {
  char symbol;
  struct __lnode * next;
} slist;

int add_symbol( slist ** list, char symbol )
{
  slist * tmp;

  if( *list == NULL )
    {
      *list = (slist*) malloc( sizeof(slist));
      if( *list == NULL )
	{
	  return 0;
	}

      (**list).next = NULL;
      (**list).symbol = symbol;
    }
  else
    {
      tmp = *list;
      while( (*tmp).next != NULL )
	{
	  tmp = (*tmp).next;
	}

      (*tmp).next = (slist*) malloc(sizeof(slist));
      tmp = (*tmp).next;
      (*tmp).next = NULL;
      (*tmp).symbol = symbol;
    }
  return 1;
}

int move_right( slist ** list )
{
  if( *list == NULL )
    {
      // case doesn't make sense
      return 0;
    }
  else
    {
      if( (**list).next == NULL )
	{
	  (**list).next = (slist*) malloc(sizeof(slist));
	  *list = (**list).next;
	  (**list).next = NULL;
	  (**list).symbol = 'B';
	}
      else
	{
	  *list = (**list).next;
	}
      return 1;
    }
}

int move_left( slist ** list, slist * tape )
{
  if( *list  == NULL || tape == NULL )
    {
      // case doesn't make sense
      return 0;
    }
  else
    {
      while( (*tape).next != NULL )
	{
	  if( (*tape).next == (*list) )
	    {
	      *list = tape;
	      return 0;
	    }     
	}
      return 0;
    }
}

int add_rule( llist ** list, unsigned int state, char symbol, char action, unsigned int next_state )
{
  /* variables */
  inst * rule;
  llist * node;
  /************/

  rule = (inst*) malloc(sizeof(inst));
  if( NULL == rule )
    {
      return 0;
    }
  (*rule).state = state;
  (*rule).symbol = symbol;
  (*rule).action = action;
  (*rule).next_state = next_state;

  node = (llist*) malloc(sizeof(llist));
  if( NULL == node )
    {
      return 0;
    }
  (*node).rule = rule;
  (*node).next = (*list);
  *list = node;
  return 1;
}

int main( int argc, char ** argv )
{
  /* Variables */
  FILE *pInput;
  FILE *pOutput;
  char line[MAX_STR], symbol, action, *output_str;
  unsigned int state, next_state, curr_state, curr_size, tracker;
  llist *rules, *tmp;
  slist *tape, *head;

  /* Init Vars */
  pOutput = stdout;
  rules = NULL;
  tape = NULL;
  head = NULL;
  tmp = NULL;

  if( argc == 1 )
    {
      pInput = stdin;
    }
  else if( argc == 2)
    {
      pInput = fopen( argv[1], "r");
      if( NULL == pInput )
	{
	  perror("fopen()");
	  exit(EXIT_FAILURE);
	}
    }
  else
    {
      fputs("usage ./turing (optional) <input-file>\n", stderr);
      exit(EXIT_FAILURE);
    }

  curr_state = READ_RULE;
  while( 1 )
    {
      if( curr_state == READ_RULE )
	{
	  if( NULL != fgets( line, MAX_STR, pInput ) )
	    {
	      if( 4 == sscanf( line, "%u %c %c %u\n", &state, &symbol, &action, &next_state ) )
		{
		  // found a rule, so add it
		  add_rule( &rules, state, symbol, action, next_state );
		}
	      else
		{
		  // didn't find a rule so move to next curr_state
		  curr_state = READ_START;
		}
	    }
	  else
	    {
	      perror("format");
	      exit(EXIT_FAILURE);
	    }
	}
      else if( curr_state == READ_START )
	{
	      if( sscanf( line, "%*s %u\n", &next_state ) == 1 )
		{
		  // got the initial state
		  curr_state = READ_TAPE;
		}
	      else
		{
		  perror("start rule format incorrect");
		  exit(EXIT_FAILURE);
		}
	}
      else if( curr_state == READ_TAPE )
	{
	  if( NULL != fgets( line, MAX_STR, pInput ) )
	    {
	      if( 1 == sscanf(line, "%c\n", &symbol ) )
		{
		  add_symbol( &tape, symbol );
		}
	      else
		{
	          perror("tape format error");
		  exit(EXIT_FAILURE);
		}
	    }
	  else
	    {
	      head = tape;
	      while( head != NULL )
		{
		  head = (*head).next;
		}
	      // last tape input
	      head = tape;
	      curr_state = EXECUTE;
	    }
	  
	}
      else if( curr_state == EXECUTE )
	{
	  tmp = rules;
	  while( tmp != NULL )
	    {
	      if( (*(*tmp).rule).state == next_state && (*(*tmp).rule).symbol == (*head).symbol )
		{
		  break;
		}
	      else
		{
		  tmp = (*tmp).next;
		}
	    }

	  if( NULL == tmp )
	    {
	      // couldn't find a matching rule
	      curr_state = END;
	    }
	  else
	    {
	      action = (*(*tmp).rule).action;
	      if( action == '1' || action == 'B' )
		{
		  (*head).symbol = action;
		}
	      else if( action == 'R' )
		{
		  move_right( &head );
		}
	      else if( action == 'L' )
		{
		  move_left( &head, tape );
		}
	      else
		{
		  perror("action format incorrect");
		  exit(EXIT_FAILURE);
		}
	   
	      next_state = (*(*tmp).rule).next_state;
	    }
	}
      else if( curr_state == END )
	{
	  head = tape;
	  //state = 0;
	  //curr_state = 0;
	  curr_size = 0;
	  tracker = 0;
	  /*
	  while( head != NULL )
	    {
	      state++;
	      if( ! curr_state )
		{
		  curr_state = ( (*head).symbol == '1' ) ? 1 : 0;
		}

	      if( curr_state )
		{
		  fprintf( pOutput, "%c", (*head).symbol );
		}
	      head = (*head).next;
	    }
	  */

	  while( head != NULL )
	    {
	      if( curr_size == 0 )
		{
		  // haven't found a 1 yet
		  if( (*head).symbol == '1' )
		    {
		      //found the first instance of a 1
		      output_str = (char*) malloc( sizeof(char) * CLUSTER_SIZE );
		      if( NULL == output_str )
			{
			  perror("malloc() output_str");
			  exit(EXIT_FAILURE);
			}

		      tracker = 0;
		      output_str[curr_size] = '1';
		      curr_size++;
		    }
		  //else go to next
		}
	      else if( curr_size )
		{
		  // add to output
		  if( ( output_str[curr_size] = (*head).symbol ) == '1' )
		    {
		      // mark the last '1' that was found
		      tracker = curr_size + 1;
		    }
		  
		  // check if we need to reallocate
		  if( curr_size % CLUSTER_SIZE  == 0 )
		    {
		      output_str = (char*) realloc( output_str, ( curr_size + CLUSTER_SIZE ) * sizeof(char) );
		    }
		  curr_size++;
		}
	 
	      head = (*head).next;
	    }
	  
	  if( !curr_size )
	    {
	      fprintf( pOutput, "B" );
	    }
	  else
	    {
	      for( curr_size = 0; curr_size < tracker; ++curr_size )
		{
		  fprintf( pOutput, "%c", output_str[curr_size] );
		}
	    }
 	  fprintf( pOutput, "\n" );
	  break;
	}
      else
	{
	  perror("curr_state incorrect");
    	  exit(EXIT_FAILURE);
	}
    }

  head = tape;
  while( (*head).next != NULL )
    {
      tape = (*head).next;
      free(head);
      head = tape;
    }

  tmp = rules;
  while( (*tmp).next != NULL )
    {
      rules = (*tmp).next;
      free( (*tmp).rule );
      free( tmp );
      tmp = rules;
    }

  exit(EXIT_SUCCESS);
}
