#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define END UINT_MAX
#define WALL ( UINT_MAX - 1)
#define START 0
#define INFINITY ( UINT_MAX - 2 )

#define IS_PORTAL_ENTRANCE( x ) ( ( x >= '1' ) && ( x <= '9' ) )
#define IS_PORTAL_EXIT( x ) ( ( x >= 'a' ) && ( x <= 'i' ) )

/*====================== TYPES =================================*/
typedef unsigned int uint;

typedef enum { FALSE = 0, TRUE } boolean;

typedef struct __point_type {
    uint x;
    uint y;
} point_type; 

typedef struct __move_type {
    point_type vertice;
    char move;
} move_type;

/*===================== FUNCTIONS =============================*/
inline uint get_portal_entrance_number( int c )
{
    return (c - '0');
}

inline uint get_portal_exit_number( int c )
{
    return( c - 96 );
}

point_type get_smallest_dist( uint ** dist, boolean ** visited, uint max_x, uint max_y ) {
    uint i, j, lowest;
    point_type lowest_point;

    lowest_point.x = INFINITY;
    lowest_point.y = INFINITY;
    lowest         = INFINITY;

    for( i = 0; i < max_y; ++i )
    {
        for( j = 0; j < max_x; ++j )
        {
            if( !visited[i][j] && ( dist[i][j] < lowest ) )
            {
                lowest = dist[i][j];
                lowest_point.y = i;
                lowest_point.x = j;
            }
        }
    }

    return lowest_point;
}

void reconstruct_path( move_type ** previous, point_type point, point_type start )
{
    if( previous[point.y][point.x].vertice.x == start.x && previous[point.y][point.x].vertice.y == start.y )
    {
        if( previous[point.y][point.x].move != ' ' )
        {
            printf("%c", previous[point.y][point.x].move);
        }
        return;
    }
    else
    {
        point_type prev_point;
        prev_point = previous[point.y][point.x].vertice;
        reconstruct_path( previous, prev_point, start );

        if( previous[point.y][point.x].move != ' ' )
        {   
            printf("%c", previous[point.y][point.x].move);
        }
    }
}

/* assumes that only want 1 shortest path all shortest paths if multiple exist */
void dijkstra( uint ** dist, boolean ** visited, uint max_x, uint max_y, uint start_x, uint start_y, uint end_x, uint end_y, point_type in_portals[9], point_type out_portals[9] )
{
    /* Variables */
    uint i, j, new_dist;
    point_type u;
    move_type ** previous;
    /* \\Variables */

    previous = (move_type**) malloc( sizeof( move_type* ) * max_y );

    if( NULL == previous )
    {
        fputs( "Unable to allocate memory!\n", stderr );
        return;
    }

    for( i = 0; i < max_y; ++i )
    {
        previous[i] = (move_type*) malloc( sizeof( move_type ) * max_x );
        if( NULL == previous[i] )
        {
            fputs( "Unable to allocate memory!\n", stderr );
            return;
        }
    }

    for( i = 0; i < max_y; ++i )
    {
        for( j = 0; j < max_x; ++j )
        {
            previous[i][j].vertice.x = INFINITY;
            previous[i][j].vertice.y = INFINITY;
            previous[i][j].move = ' ';
        }
    }

    while( 1 )
    {
        u = get_smallest_dist( dist, visited, max_x, max_y );

        if( u.x == INFINITY || u.y == INFINITY )
        {
            break;
        }
        else
        {
            visited[u.y][u.x] = TRUE;
            new_dist = dist[u.y][u.x];

            /* check if we hit the end */
            if( u.x == end_x && u.y == end_y )
            {
                /* reconstruct the path */
                point_type start, end;
                start.x = start_x;
                start.y = start_y;
                end.x = end_x;
                end.y = end_y;
                
                reconstruct_path( previous, end, start );
                return;
                //break;
            }           

            boolean is_portal_entrance = FALSE;
            uint portal_number;

            for( i = 0; i < 9; ++i )
            {
                if( u.x == in_portals[i].x && u.y == in_portals[i].y )
                {
                    is_portal_entrance = TRUE;
                    portal_number = i;
                    break;
                }
            }

            /* if it is a portal entrance then update the portal exit only */
            if( is_portal_entrance )
            {
                point_type exit = out_portals[portal_number];
                if( !visited[exit.y][exit.x] && new_dist < dist[exit.y][exit.x] )
                {
                    dist[exit.y][exit.x] = new_dist;
                    previous[exit.y][exit.x].vertice.x = u.x;
                    previous[exit.y][exit.x].vertice.y = u.y;
                }
            }
            /* otherwise, update all unvisited vertices */
            else
            {
            
                uint new_x, new_y;
                boolean far_left, far_top;
                far_left = FALSE;
                far_top = FALSE;

                /* all edges are distance 1 for this maze */
                new_dist++;

                if( new_x == 0 )
                {
                    far_left = TRUE;
                }
                if( new_y == 0 )
                {
                    far_top = TRUE;
                }
                /* check above */
                if( !far_top )
                {
                    new_x = u.x;
                    new_y = u.y - 1;
                
                    /* check if on graph */
                    if( ( new_x >= 0 ) && ( new_x < max_x ) && ( new_y < max_y ) && !visited[new_y][new_x] && dist[new_y][new_x] != WALL && new_dist < dist[new_y][new_x] )
                    {
                        dist[new_y][new_x] = new_dist;
                        previous[new_y][new_x].move = 'u';
                        previous[new_y][new_x].vertice.x = u.x;
                        previous[new_y][new_x].vertice.y = u.y;
                    }
                }

                /* check below */
                new_x = u.x;
                new_y = u.y + 1;
                if( ( new_x >= 0 ) && ( new_x < max_x ) && ( new_y >= 0 ) && ( new_y < max_y ) && !visited[new_y][new_x] && dist[new_y][new_x] != WALL && new_dist < dist[new_y][new_x] )
                {
                    dist[new_y][new_x] = new_dist;
                    previous[new_y][new_x].move = 'd';
                    previous[new_y][new_x].vertice.x = u.x;
                    previous[new_y][new_x].vertice.y = u.y;

                }

                /* check left */
                if( !far_left )
                {
                    new_x = u.x - 1;
                    new_y = u.y;
                    if( ( new_x < max_x ) && ( new_y >= 0 ) && ( new_y < max_y ) && !visited[new_y][new_x] && dist[new_y][new_x] != WALL && new_dist < dist[new_y][new_x] )
                    {
                        dist[new_y][new_x] = new_dist;
                        previous[new_y][new_x].move = 'l';
                        previous[new_y][new_x].vertice.x = u.x;
                        previous[new_y][new_x].vertice.y = u.y;
                    }
                }

                /* check right */
                new_x = u.x + 1;
                new_y = u.y;
                if( ( new_x >= 0 ) && ( new_x < max_x ) && ( new_y >= 0 ) && ( new_y < max_y ) && !visited[new_y][new_x] && dist[new_y][new_x] != WALL && new_dist < dist[new_y][new_x] )
                {
                    dist[new_y][new_x] = new_dist;
                    previous[new_y][new_x].move = 'r';
                    previous[new_y][new_x].vertice.x = u.x;
                    previous[new_y][new_x].vertice.y = u.y;
                }
            
            }
        }
    }
}

void solve( uint ** dist, boolean ** visited, uint h, uint w, point_type start, point_type end, point_type in_portals[9], point_type out_portals[9] )
{
    dijkstra( dist, visited, w, h, start.x, start.y, end.x, end.y, in_portals, out_portals );
}

/*=================================== MAIN ======================================*/

int main( int argc, char ** argv )
{
    /******* Variables *******/
    FILE * pFile = NULL;
    uint h,w,i,j,t;
    uint ** dist;
    boolean ** visited;
    uint portal_count;
    point_type out_portals[9];
    point_type in_portals[9];
    point_type start, end;
    int c;
    /******* End Variables ********/

    /* Open input */
    /* Determine method of input */
    if( argc == 1) {
        pFile = stdin;
    } else if( argc == 2) { 
        pFile = fopen( argv[1], "r" ); 
        
        if( NULL == pFile )
        {
            fputs( "Could not open input file!\n", stderr );
            return(-1);
        }
    } else {
        fputs( "Usage: ./hackman <inputfile>\n<inputfile> (optional): the maze input.", stderr);
        return(-2);
    }
    /* Get height and width */
    if( 2 != fscanf( pFile, "%u %u\n", &h, &w) )
    {
        fputs( "Incorrect formatting!\n", stderr );
        return(-3);
    }

    /* initialize arrays */
    /* initialize dist */
    dist = (uint**) malloc( sizeof( uint* ) * h );

    if( NULL == dist )
    {
        fputs( "Unable to allocate memory!\n", stderr );
        return(-4);
    }

    for( i = 0; i < h; ++i )
    {
        dist[i] = (uint*) malloc( sizeof( uint ) * w );
        if( NULL == dist[i] )
        {
            fputs( "Unable to allocate memory!\n", stderr );
            return(-5);
        }
    }

    /* initialize visited */
    visited = (boolean**) malloc( sizeof( boolean* ) * h );

    if( NULL == visited )
    {
        fputs( "Unable to allocate memory!\n", stderr );
        return(-4);
    }

    for( i = 0; i < h; ++i )
    {
        visited[i] = (boolean*) malloc( sizeof( boolean ) * w );
        if( NULL == visited[i] )
        {
            fputs( "Unable to allocate memory!\n", stderr );
            return(-5);
        }
    }

    /* init portals */
    portal_count = 0;

    for( i = 0; i < 9; ++i )
    {
        out_portals[i].x = INFINITY;
        out_portals[i].y = INFINITY;
        in_portals[i].x  = INFINITY;
        in_portals[i].y  = INFINITY;
    }

    /* Read in the maze */
    /* If the character is:
     *      +start: set to dist[start] START, record position, visited[start] = 0
     *      +end: set dist[end] to END, visited[end] = 0
     *      +wall: set dist[wall] to INFINITY, visited[wall] = 1
     *      +portal (entrance): set dist[portal] to INFINITY, visited[portal entrance] = 0
     *      +portal (exit): set dist[portal] to INFINITY, visited[portal exit] = 0
     *      +space: set dist[space] to INFINITY, visited[space] = 0
     */
    for( i = 0; i < h; ++i )
    {
        for( j = 0; j < w; ++j )
        {
            c = fgetc( pFile );
            
                if( c == '*' ) {
                    dist[i][j] = WALL;
                    visited[i][j] = TRUE;
                } else if( c == 'S' ) {
                    dist[i][j] = START;
                    start.x = j;
                    start.y = i;
                    visited[i][j] = FALSE;
                } else if( c == '@' ) {
                    dist[i][j] = END;
                    end.x = j;
                    end.y = i;
                    visited[i][j] = FALSE;
                } else if( IS_PORTAL_ENTRANCE( c ) ) {
                    /* is a number for a portal entrance */
                    dist[i][j] = INFINITY;
                    visited[i][j] = FALSE;
                    t = get_portal_entrance_number( c );
                    t--;
                    in_portals[t].x = j;
                    in_portals[t].y = i;
                    portal_count++;
                } else if( IS_PORTAL_EXIT( c ) ) {
                    /* is a lower-case letter for a portal exit */
                    t = get_portal_exit_number( c );
                    t--;
                    out_portals[t].x = j;
                    out_portals[t].y = i;
                    dist[i][j] = WALL;
                    visited[i][j] = FALSE;
                } else {
                    /* is just a space */
                    dist[i][j] = INFINITY;
                    visited[i][j] = FALSE;
                }
        }

        /* get the newline character */
        c = fgetc( pFile );
        if( c != '\n' )
        {
            fputs( "Formatting incorrect!\n", stderr );
            return( -6 );
        }
    }

    /* check that each portal entrance has corresponding exit (naive check) */
    for( i = 0; i < 9; ++i )
    {
        if( out_portals[i].x == INFINITY )
        {
            break;
        }
    }

    if( i != portal_count )
    {
        fputs( "Portals not correct!\n", stderr );
        return(-6);
    }

    fclose( pFile );

    solve( dist, visited, h, w, start, end, in_portals, out_portals );

    printf("\n"); // the output has a newline, append that so my diffs works...
    for( i = 0; i < h; ++i )
    {
        free( dist[i] );
        free( visited[i] );
    }
    free( dist );
    free( visited );
    return(0);
}
/* FIN :-#) */
