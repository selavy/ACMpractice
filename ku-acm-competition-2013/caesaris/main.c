#include <stdio.h>
#include <stdlib.h>

#define IS_ALPHA( x ) ( ( ( x > 64 ) && ( x < 91 ) ) ||  ( ( x > 96 ) && ( x < 123 ) ) )
#define IS_UPPER( x ) ( ( x > 64 ) && ( x < 91 ) )
#define UPPER_TO_NUM( x ) ( x - 65 )
#define LOWER_TO_NUM( x ) ( x - 97 )
#define SHIFT( x, y ) ( ( x + y < 26 ) ? x + y : 24 - x + y )

typedef unsigned int uint;

int main( int argc, char ** argv ) {
    FILE * pFile;
    char c;
    uint i, j, letter_count, best_shift;
    double tmp;
    double best, current;
    uint alpha[26];
 
    uint ideal[] = { 0.08167, 0.01492, 0.2782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 };

    if( argc != 2 )
    {
        fputs( "usage: ./caesaris <input-file>\n", stderr );
        return(-1);
    }
    else
    {
        pFile = fopen( argv[1], "r" );
        
        if( NULL == pFile )
        {
            fputs( "Unable to open input file!\n", stderr );
            return(-2);
        }
    }

    for( i = 0; i < 26; ++i )
    {
        alpha[i] = 0;
    }

    letter_count = 0;
   
    c = fgetc( pFile );
    while( c != EOF )
    {
        c = fgetc( pFile );

        if( IS_ALPHA( c ) )
        {
            letter_count++;
            if( IS_UPPER( c ) )
            {
                alpha[ UPPER_TO_NUM( c ) ]++;
            }
            else
            {
                alpha[ LOWER_TO_NUM( c ) ]++;
            }
        }
    }

    best = 1000;
    best_shift = 0;

    for( i = 0; i < 25; ++i )
    {
        current = 0;
        for( j = 0; j < 25; ++j )
        {
            tmp = (float) alpha[SHIFT(i,j)] / letter_count;            
            tmp -= ideal[j];
            tmp = ( tmp < 0 ) ? -1 * tmp : tmp;
            current += tmp;
        }

        if( current < best )
        {
            best = current;
            best_shift = i;
        }

    }

    rewind( pFile );

    c = fgetc( pFile );
    while( c != EOF )
    {
       if( IS_ALPHA( c ) )
       {
           fputc( SHIFT( c, best_shift ), stdout );
       }
       else
       {
           fputc( c, stdout );
       }
    }

    fclose( pFile );

    return 0;
}
