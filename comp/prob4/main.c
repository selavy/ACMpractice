#include <stdio.h>
#include <string.h>

int convert( char);
int in_limit(char);

int main() {
    char str[2056];
    fgets( str, 2056, stdin );
    int length = strlen( str );
    int i;
    for( i = 0; i < length && str[i] != '\0'; ++i )
    {
        if( str[i] == 'x' )
        {
            if( ((i+1) < length) && ((i+2) < length) && in_limit( str[i+1] ) && in_limit( str[i+2] ) )
            {
                char cc = convert( str[i+1] ) * 16 + convert( str[i + 2]);
                if( (cc > 32) && (cc < 127))
                    printf("%c", cc);
            }
        }
    }
            
    printf("\n");
    return 0;
}

int convert( char c )
{
    switch( c )
    {
        case 48:
            return 0;
            break;
        case 49:
            return 1;
            break;
        case 50:
            return 2;
            break;
        case 51:
            return 3;
            break;
        case 52:
            return 4;
            break;
        case 53:
            return 5;
            break;
        case 54:
            return 6;
            break;
        case 55:
            return 7;
            break;
        case 56:
            return 8;
            break;
        case 57:
            return 9;
            break;
        case 65:
        case 97:
            return 10;
            break;
        case 66:
        case 98:
            return 11;
            break;
        case 67:
        case 99:
            return 12;
            break;
        case 68:
        case 100:
            return 13;
            break;
        case 69:
        case 101:
            return 14;
            break;
        case 70:
        case 102:
            return 15;
            break;
        default:
            return 0;
    }
}



int in_limit( char c )
{
    if( (c > 47) && (c < 58) )
    {
        return 1;
    }
    else if( (c > 64) && (c < 71) )
    {
        return 1;
    }
    else if( (c > 96) && (c < 103) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

