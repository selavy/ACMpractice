#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main() {
    string str;
    while(cin >> str )
    {
        int sharps[7], flats[7];
        for( int i = 0; i < 7; ++i )
        {
            sharps[i] = 0;
            flats[i] = 0;
        }
        
        int length = str.length();
        for( int i = 0; i < length; ++i )
        {
            if( str.at(i) == '#' )
            {
                if( i - 1 > 0)
                {
                switch( str.at(i - 1) )
                {
                    case 'A':
                        sharps[0] = 1;
                        break;
                    case 'B':
                        sharps[1] = 1;
                        break;
                    case 'C':
                        sharps[2] = 1;
                        break;
                    case 'D':
                        sharps[3] = 1;
                        break;
                    case 'E':
                        sharps[4] = 1;
                        break;
                    case 'F':
                        sharps[5] = 1;
                        break;
                    case 'G':
                        sharps[6] = 1;
                        break;
                    default:
                        break;
                }
                }
            }
            else if( str.at(i) == 'b' )
            {
                if( i - 1 > 0 )
                {
                switch( str.at(i - 1 ) )
                {
                    case 'A':
                        flats[0] = 1;
                        break;
                    case 'B':
                        flats[1] = 1;
                        break;
                    case 'C':
                        flats[2] = 1;
                        break;
                    case 'D':
                        flats[3] = 1;
                        break;
                    case 'E':
                        flats[4] = 1;
                        break;
                    case 'F':
                        flats[5] = 1;
                        break;
                    case 'G':
                        flats[6] = 1;
                        break;
                    default:
                        break;
                }
                }
            }
    }

        int sharps_c = 0;
        int flats_c = 0;
        for( int i = 0; i < 7; ++i )
        {
            if(sharps[i])
                sharps_c++;
            else if ( flats[i] )
                flats_c++;
        }

        if( sharps_c == 1 )
            printf("G major\n");
        else if( sharps_c == 2)
            printf("D major\n");
        else if( sharps_c == 3)
            printf("A major\n");
        else if( sharps_c == 4)
            printf("E major\n");
        else if( sharps_c == 5)
            printf("B major\n");
        else if( sharps_c == 6)
            printf("F# major\n");
        else if(sharps_c == 7)
            printf("C# major\n");
        else
        {
            if(flats_c == 1)
                printf("F major\n");
            else if(flats_c == 2)
                printf("Bb major\n");
            else if(flats_c == 3)
                printf("Eb major\n");
            else if(flats_c == 4)
                printf("Ab major\n");
            else if(flats_c == 5)
                printf("Db major\n");
            else if(flats_c == 6)
                printf("Gb major\n");
            else if(flats_c == 7)
                printf("Cb major\n");
            else
            {
                printf("C major\n");
            }
        }

    }
    return 0;
}
