#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main( int argc, char ** argv ) {
    FILE * pOut;

    if( argc == 3 ) {
        pOut = fopen( "input3.txt", "w" );
    } else if( argc == 4 ) {
        pOut = fopen( argv[3], "w" );
    } else {
        fputs( "usage: ./generate <number_of_books> <number_of_scribes> <output-file>\n", stderr );
        return(-1);
    }

    if( NULL == pOut )
    {
        fputs( "Unable to open output file!\n", stderr );
        return(-1);
    }

    srand( time( NULL ) );

    fprintf( pOut, "%s %s\n", argv[1], argv[2] );
    
    unsigned int i, n;
    n = strtol( argv[1], NULL, 10 );

    for( i = 0; i < n; ++i )
    {
        fprintf( pOut, "%d\n", ( rand() % 500 ) );
    }

    fclose( pOut );

    return 0;
}
