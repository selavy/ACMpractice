#include <iostream>
#include <cmath>
#include <cstdio>

#define PI 3.141592654
#define G 9.8

using namespace std;

int main() 
{
    int d, v;
    while( scanf("%d %d", &d, &v) != EOF )
    {
        float i = G*d/(v*v);
        float angle = asin(i)/2*180/PI;
        if( i < 0 || i > 1 )
            printf("no possible angle\n");
        else
        {
            printf("%.4f\n", angle );
        }
    }
    return 0;
}
