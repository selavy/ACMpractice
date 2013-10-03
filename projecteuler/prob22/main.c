#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main( int argc, char ** argv ) {
  vector<string> names;

  if( argc != 2 )
    {
      cout << "usage: ./prob22 <inputfile>\n" << endl;
      return 1;
    }

  ifstream is(argv[1]);

  if(! is.good() )
    {
      cout << "unable to open input file!" << endl;
      return 1;
    }

  char c;
  bool matching_parens = true;
  string current_name = "";
  while( is.good() )
    {
      c = is.get();
      if( is.good() )
	{
	  if( c == '\"' )
	    {
	      matching_parens ^= true;
	      if( matching_parens )
		{
		  names.push_back( current_name );
		  current_name = "";
		}
	    }
	  else if( c != ',' && c != ' ' )
	    {
	      current_name.push_back(c);
	    }

	}
    }

      sort( names.begin(), names.end() );
      vector<string>::iterator it;
      unsigned long long i = 1;
      unsigned long long score = 0;
      unsigned long long tmp = 0;
      string str = "";
      unsigned short j;
      for( it = names.begin(); it != names.end(); ++it )
	{
	  str = *it;
	  tmp = 0;
	  for( j = 0; j < str.size(); ++j )
	    {
	      tmp += ( str.at(j) - 64 );
	    }
	  score += ( tmp * i );
	  i++;
	}
      cout << score << endl;
      return 0;
}
