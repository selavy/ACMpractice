#include <stdio.h>
#include <stdlib.h>

int main() {
    int w, h;
    while( scanf("%d %d", &w, &h ) != EOF )
    {
        int * image1;
        image1 = (int*) malloc(sizeof(int) * w * h * 3 );
        int i;
        int limit = w * h * 3;
        for( i = 0; i < limit; ++i )
        {
            scanf("%d", image1[i]);
        }
        scanf("%d %d", &w, &h );
        int * image2;
        image2 = (int*) malloc(sizeof(int) * w * h * 3 );
        for( i = 0; i < limit; i = ++i )
        {
            scanf("%d", image2[i] );
        }
        
        printf("%d %d\n", w, h );
        
        for( i = 0; i < limit - 1; ++i )
        {
            printf("%d ", (image1[i] + image2[i]) / 2 );
        }
        printf("%d", (image1[limit - 1] + image2[limit - 1])/2);
        printf("\n");
    }
    return 0;
}
