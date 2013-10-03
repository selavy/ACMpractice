#include <stdio.h>

int main( int argc, char ** argv )
{
  unsigned int day, day_in_week, month, year, counter, limit;
  year = 1900;
  day = 1;
  day_in_week = 1;
  month = 1;
  counter = 0;
  limit = 0;

  while( year <= 2000 )
    {
      if( day_in_week >= 7 )
	{
	  // it is a sunday
	  if( day == 1 && year != 1900 )
	    {
	      // 1st of the month
	      counter++;
	    }
	  day_in_week = 1;
	}
      else
	{
	  day_in_week++;
	}

      switch( month )
	{
	  //jan
	case 1:
	  // march
	case 3:
	  //may
	case 5:
	  //july
	case 7:
	  //august
	case 8:
	  //october
	case 10:
	  //dec
	case 12:
	  limit = 31;
	  break;
	  //feb
	  //28 usually
	  //29 on leap year => year divisible by 4, unless century
	  //then if divisible by 400
	case 2:
	  // don't need to worry about the century, since only change is 1900 => 2000 and that is divisible by 400
	  if( year % 4 == 0 )
	    {
		  limit = 29;
	    }
	  else
	    {
	      limit = 28;
	    }
	  break;
	  //april
	case 4:
	  //june
	case 6:
	  //nov
	case 11:
	  //sep
	case 9:
	  limit = 30;
	  break;
	default:
	  limit = 31;
	}

      // limit now holds the number of days in the current month
      day++;
      if( day > limit )
	{
	  day = 1;
	  month++;
	  if( month > 12 )
	    {
	      month = 1;
	      year++;
	    }
	}
    }

  printf("%d\n", counter);
  return 0;
}
