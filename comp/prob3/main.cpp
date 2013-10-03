#include <iostream>

using namespace std;

int main() 
{
    int w, h;
    while( cin >> w >> h )
    {
        int limit = w * h * 3;
        int * image1 = new int[limit];
        for( int i = 0; i < limit; ++i )
        {
            cin >> image1[i];
        }

        cin >> w >> h;

        int * image2 = new int[limit];
        for( int i = 0 ; i < limit; ++i )
        {
            cin >> image2[i];
        }

        cout << w << " " << h << endl;
        for( int i = 0; i < (limit - 1); ++i )
        {
            cout << (image1[i] + image2[i])/2 << " ";
        }
        cout << (image1[limit - 1] + image2[limit - 1])/2 << endl;
    }
    return 0;
}
