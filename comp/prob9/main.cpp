#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int convert( char c );
char shift( char c, int shift );
int main() {
    string input;
    getline( cin, input );

    int alpha[26];
    for ( int i = 0; i < 26; ++i )
        alpha[i] = 0;

    int count = 0;
    int index;
    for( int i = 0; i < input.length(); ++i )
    {
       index = convert( input.at(i) );
       if( index != -1 )
       {
           count++;
           alpha[index]++;
       }
    }

    int correct[26];
    correct[0] = .08167 * count;
    correct[1] = .01492 * count;
    correct[2] = .02782 * count;
    correct[3] = .04253 * count;
    correct[4] = .012702 * count;
    correct[5] = .02228 * count;
    correct[6] = .02015 * count;
    correct[7] = .06094 * count;
    correct[8] = .06966 * count;
    correct[9] = .00153 * count;
    correct[10] = .00772 * count;
    correct[11] = .04025 * count;
    correct[12] = .02406 * count;
    correct[13] = .06749 * count;
    correct[14] = .07507 * count;
    correct[15] = .01929 * count;
    correct[16] = .00095 * count;
    correct[17] = .05987 * count;
    correct[18] = .06327 * count;
    correct[19] = .09056 * count;
    correct[20] = .02758 * count;
    correct[21] = .00978 * count;
    correct[22] = .02360 * count;
    correct[23] = .00150 * count;
    correct[24] = .01974 * count;
    correct[25] = .00074 * count;

    int min = 10000;
    int tryalpha[26];
    int num = 0;
    for ( int i = 0; i < 26; ++i )
    {
        for( int t = 0; t < 26; ++t)
            tryalpha[t] = 0;
        int d = 0;
        for( int j = 0; j < input.length(); ++j )
        {
            int ii = convert( shift(input.at(j), i) );
            if( ii != -1 )
               tryalpha[ii]++;
        }
        for ( int t = 0; t < 26; ++t )
            d += (int) abs(correct[t] - tryalpha[t] );

        if( d < min )
        {
            min = d;
            num = i;
        }
    }

    num++;
    for( int i = 0; i < input.length(); ++i )
    {
        if( (input.at(i) > 64 && input.at(i) < 91) || (input.at(i) < 123 && input.at(i) > 96) )
            cout << (char) shift(input.at(i), num);
        else
            cout << input.at(i);
    }
    return 0;
}

int convert( char c ) {
    if( (c < 91) && (c > 64) )
        return c - 65;
    else if( ( c < 123 ) && ( c > 96 ) )
        return c - 96;
    else
        return -1;
}

char shift( char c, int shift ) {
    if( ( c < 91 ) && (c > 64 ) )
    {
        if( c + shift > 90 )
        {
            return 64 + (c + shift - 90);
        }
        else
            return c + shift;
    }
    else
    {
        if( c + shift > 122 )
        {
            return 96 + (c + shift - 122);
        }
        else
            return c + shift;
    }
}
