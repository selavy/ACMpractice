#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lowest( int*, int);

int main() {
    int n, m;

    cin >> n >> m;

    int * scribes = new int[m];
    vector<int> pages;

    for ( int i = 0; i < m; ++i )
        scribes[i] = 0;

    int page;
    for(int i = 0; i < n; ++i)
    {
        cin >> page;
        pages.push_back(page);
    }


    sort( pages.begin(), pages.end() );

    int index;
    while(! pages.empty() )
    {
        index = lowest(scribes, m);
        scribes[ index ] += pages.back();
        pages.pop_back();

    }

    int max = 0;
    for( int i = 0; i < m; ++i )
    {
        if( scribes[i] > max )
            max = scribes[i];
    }
    printf("%d\n", max);
    return 0;

}

int lowest( int * s, int m )
{
    int index = 0, low = s[0];
    for( int i = 0; i < m; ++i )
    {
        if( s[i] == 0 )
            return i;
        if( s[i] < low )
        {
            low = s[i];
            index = i;
        }
    }
    return index;
}


