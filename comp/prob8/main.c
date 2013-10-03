#include <stdio.h>
#include <stdlib.h>

int main() {
    int h, w;
    scanf("%d %d", &h, &w);
    
    char ** board;
    board = (char**) malloc( h* sizeof(char*));
    int i;
    for( i = 0; i < h; ++i )
        board[i] = (char*) malloc( w* sizeof(char));


    int x, y;
    for( y = 0; y < h; ++y )
    {
            fread( board[y], sizeof(char), w, stdin );
    }

    for ( y = 0; y < h; ++y )
    {
        for ( x = 0; x < w; ++x )
        {
            printf("%c", board[y][x]);
        }
