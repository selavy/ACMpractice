#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DENSITY 2750
int main() {
    int x, y, h, w, d;
    int M = 0;
    int x_axis = 0;
    int y_axis = 0;

    while( scanf("%d %d %d %d %d",  &x, &y, &h, &w, &d ) != EOF )
    {
        int mass = abs(w*d*h*DENSITY);
        M += mass;
        x_axis += x*mass;
        y_axis += y*mass;
    }

    printf("%d %d\n", x_axis / M, y_axis / M );



    return 0;
}
