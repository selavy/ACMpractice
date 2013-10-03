#include <stdio.h>
#include <ncurses.h>

void print_board( int (*board)[3] ) {
  unsigned int i, j;
  for( i = 0; i < 3; ++i )
    {
      for( j = 0; j < 3; ++j )
	{
	  if( board[i][j] == 1 )
	    {
	      printw(" X ");
	    }
	  else if( board[i][j] == 2 )
	    {
	      printw(" O ");
	    }
	  else
	    {
	      printw("   ");
	    }

	  if( j != 2 )
	    {
	      printw("|");
	    }
	}

       if( i != 2 )
	{
	  printw("\n-----------\n");
	}
    }
}

int computer_move( int (*board)[3] ) {

  return 1;
}

int get_move( int (*board)[3] ) {
  int input;
  char str[512];

  printw("\nWhere would you like to move? (1-9): ");
  
  getstr(str);
  input = str[0];
  
  if( input < 58 && input > 48 )
    {
      input -= '0';
    }
  
  //if( input > 9 || input < 1 )
    else
    {
      printw("\nInvalid input!\n");
      return get_move( board );
    }

  switch( input )
    {
    case 1:
      if( !board[0][0] )
	return 1;
      break;
    case 2:
      if( !board[0][1] )
	return 2;
      break;
    case 3:
      if( !board[0][2] )
	return 3;
      break;
    case 4:
      if( !board[1][0] )
	return 4;
      break;
    case 5:
      if( !board[1][1] )
	return 5;
      break;
    case 6:
      if( !board[1][2] )
	return 6;
      break;
    case 7:
      if( !board[2][0] )
	return 7;
      break;
    case 8:
      if( !board[2][1] )
	return 8;
      break;
    case 9:
      if( !board[2][2] )
	return 9;
      break;
    default:
      break;
    }

  printw("\nSpace already taken!\n");
  return get_move( board );
}

void won( int (*board)[3], int winner )
{
  erase();
  print_board(board);
  if( winner == 1 )
    {
      printw("\n\nX won!\n");
    }
  else if( winner == 2)
    {
      printw("\n\nO won!\n");
    }
  else
    {
      printw("\n\nStalemate!\n");
    }
}
  
int game_over( int (*board)[3] )
{
  int i, j;
  for( i = 0; i < 3; i++ )
    {
      if( board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2] )
	{
	  if( board[i][0] != 0 )
	    {
	      won( board, board[i][0] );
	    }

	  return 1;
	}
      if( board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i] )
	{
	if( board[0][i] != 0 )
	  {
	    won( board, board[0][i]);
	  }

	  return 1;
	}
    }

  if( board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2] )
    {
      if( board[0][0] != 0 )
	{
	  won( board, board[0][0] );
	}

      return 1;
    }

  if( board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0] )
    {
      if( board[0][2] != 0)
	{
	  won( board, board[0][2] );
	}

      return 1;
    }

for( i = 0; i < 3; ++i )
  {
    for( j = 0; j < 3; ++j )
      {
	if( board[i][j] == 0 )
	  {
	    return 0;
	  }
      }
  }

 won( board, 0 );
return 1;
}

void make_move( int (*board)[3], int square, int color )
{
  int c;

  if( color != 0 && color != 1 )
    {
      return;
    }

  if( square < 1 && square > 9 )
    {
      return;
    }

  c = color ? 2 : 1;

  switch( square )
    {
    case 1:
      board[0][0] = c;
      break;
    case 2:
      board[0][1] = c;
      break;
    case 3:
      board[0][2] = c;
      break;
    case 4:
      board[1][0] = c;
      break;
    case 5:
      board[1][1] = c;
      break;
    case 6:
      board[1][2] = c;
      break;
    case 7:
      board[2][0] = c;
      break;
    case 8:
      board[2][1] = c;
      break;
    case 9:
      board[2][2] = c;
      break;
    default:
      break;
    }
}

int main( int argc, char ** argv ) {
  initscr();

  int board[3][3];
  int i, j, n, c;

  for( i = 0; i < 3; ++i )
    {
      for( j = 0; j < 3; ++j )
	{
	  board[i][j] = 0;
	}
    }
  print_board(board);
  refresh();

  c = 0;
  do
    {
      erase();
      print_board(board);
      n = get_move(board);
      make_move(board,n,c);
      c ^= 1;
      refresh();
    }while( !game_over(board) );
  getch();
  endwin();
  return 0;
}

