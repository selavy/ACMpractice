#include <stdio.h>

int next(long long, int);

int main() {
    int m,n;
    while( scanf("%d %d", &m, &n) != EOF )
    {
        int h = 0, s = 0, v = 0;
        long long i = 0;
        for( i = m; i < n; ++i )
        {
            s = next(i, 1);
            if( s > h )
            {
                h = s;
                v = i;
            }
        }
        printf("%d\n", v);
    }
    return 0;            
}

int next( long long i, int c )
{
    if( i == 1 )
        return c;
    else if( i & 1 )
        return next( 3*i+1, ++c );
    else
        return next( i >> 1 , ++c );
}
