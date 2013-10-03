#include <stdio.h>

int main()
{
    int l = 0;
    char c;
    char str[512];
    while( scanf("%c", &c) != EOF )
    {
        if( c == '\n' )
        {
            if(!l)
                printf("balanced\n");
            else
                printf("unbalanced\n");
            l = 0;
        }
        else if( c == '(' )
            l++;
        else if( c == ')' )
        {
            l--;
            if( l < 0 )
            {
                scanf("%s", str);
            }
        }
        
    }

    return 0;
}



