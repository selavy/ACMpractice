#include <stdio.h>

int main( int argc, char ** argv ) {
    FILE * pInput;
    FILE * pOutput;
    char str[512];
    unsigned int length, i, middle;

    pOutput = stdout;

    if( 2 == argc ) {
        pInput = fopen( argv[1], "r" );
    } else if( 1 == argc ) {
        pInput = stdin;
    } else {
        fputs( "Usage: ./palindrome <file> | <string>\n", pOutput );
    }

    if( NULL == pInput ) {
        fputs( "Unable to open input!\n", pOutput );
    }


    fgets( str, 512, pInput );
    fclose( pInput );

    length = 0;

    while( '\0' != str[length] )
    {
        length++;
    }
    length--;
    
    middle = length / 2;
    middle++;
    length--;

    for( i = 0; i < middle; ++i )
    {
        if( str[i] != str[length - i] ) {
            fputs( "false\n", pOutput );
            return 0;
        }
    }

    fputs( "true\n", pOutput );
    return 0;
}


