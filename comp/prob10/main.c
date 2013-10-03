#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;

    scanf("%d %d", &n, &m);

    int * scribes;
    scribes = (int*) malloc(sizeof(int) * m);
    int i;
    int pages;
    for( i = 0; i < m; ++i )
        scribes[i] = 0;
    for( i = 0; i < n; ++i )
    {
        scanf("%d", &pages);
        scribes[lowest_scribe( scribes, m )] = pages;
    }

    int max = 0;
    for ( i = 0; i < n; ++i )
    {
        if( scribes[i] > max )
        {
            max = scribes[i];
        }
    }

    printf("%d\n", max );

    return 0;
}

int lowest_scribe( int * scribes, int n ) {
    int i;
    int lowest = 0;
    int index = 0;
    for( i = 0; i < n; ++i )
    { 
        if( scribes[i] == 0 )
            return i;
        else
        {
            if( scribes[i] < lowest )
            {
                lowest = scribes[i];
                index = i;
            }
        }
    }
    return index;
}
