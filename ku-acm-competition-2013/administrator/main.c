#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int uint;

uint maximize( uint ** pages, uint n ) {
    uint i;
    uint highest = 0;
    for( i = 0; i < n; ++i )
    {
        if( (*pages)[i] > highest )
        {
            highest = (*pages)[i];
        }
    }
    return highest;
}

uint sum( uint ** p, uint n ) {
    uint i, count;
    count = 0;
    for( i = 0; i < n; ++i )
    {
        count += (*p)[i];
    }

    return count;
}


uint find_highest( uint ** p, uint n, uint t )
{
    uint i, highest, j, current;

    highest = 0;
    for( i = 0; i < n; i += t )
    {
        current = 0;
        for( j = 0; j < t; ++j )
        {
            if( i+j < n )
            {
                current += (*p)[i+j];
            }
        }

        if( current > highest )
        {
            highest = current;
        }
    }
    
    return highest;
}
        
uint can_assign_scribes( uint ** p, uint num_books, uint num_scribes, uint max )
{
    uint i, count, scribes_needed;

    scribes_needed = 1;
    count = 0;
    for( i = 0; i < num_books; ++i )
    {
        count += (*p)[i];
        if( count > max )
        {
            scribes_needed++;
            count = (*p)[i];
        }
    }

    return ( scribes_needed <= num_scribes ) ? 1 : 0;
}


uint solve( uint ** p, uint num_books, uint scribes ) {
    uint i, max;
    for( i = 1; i < num_books; ++i )
    {
        max = find_highest( p, num_books, i );
        if( can_assign_scribes( p, num_books, scribes, max ) )
        {
            return max;
        }
    }
    return 0;
}

int main( int argc, char ** argv ) {
    FILE * pFile;
    FILE * pOutput;
    FILE * pErrorOut;
    FILE * pLog;
    uint num_scribes, num_books, i; 
    uint * pages;

    clock_t begin, end;
    double time_spent;

    pOutput = stdout;
    pErrorOut = stderr;

    if( argc != 2 )
    {
        fputs( "usage: ./administrator <input-file>\n", pErrorOut );
        return(-1);
    }
    else
    {
        pFile = fopen( argv[1], "r" );

        if( pFile == NULL )
        {
            fputs( "unable to open input file!\n", pErrorOut );
        }
    }

    if( 2 != fscanf( pFile, "%u %u\n", &num_books, &num_scribes ) )
    {
        fputs( "incorrect formatting!\n", pErrorOut );
        fclose( pFile );
        return(-2);
    }

    /* allocate page memory */
    pages = (uint*) malloc( sizeof( uint ) * num_books );

    for( i = 0; i < num_books; ++i )
    {
        if( 1 != fscanf( pFile, "%u\n", &pages[i] ) )
        {
            fputs( "incorrect formatting in pages!\n", pErrorOut );
            fclose( pFile );
            return(-3);
        }
    }

    begin = clock();
    if( num_scribes == 0 )
    {
        printf("0\n"); 
    } else if( num_scribes == 1 ) {
        printf("%u\n", sum( &pages, num_books ) );
    } else if( num_scribes >= num_books ) {
        fprintf( pOutput, "%u\n", maximize( &pages, num_books ) );
    } else {
        fprintf( pOutput, "%u\n", solve( &pages, num_books, num_scribes ) );
        //fprintf( pOutput, "%u\n", find_highest( &pages, num_books, 2 ) );
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("%f seconds\n", time_spent );

    fclose( pFile );
    pLog = fopen( "log.txt", "a" );

    if( NULL != pLog )
    {
        fprintf( pLog, "%s >> %f seconds\n", argv[1], time_spent );
        fclose( pLog );
    }
    
    return 0;
}
