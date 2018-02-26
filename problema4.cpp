#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

ifstream f("date.in.txt");
ofstream g("date.out.txt");

int n, k, a[100][100];

void construct(int n, int k)
{
    if(n != 1)
        construct(n - 1, k - a[n][k]);

    g<<a[n][k]<<" ";
}

int main()
{
    int x;
    string line;

    f>>n>>k;

    for(int i = 1;i <= k; i++)
        a[0][k] = 1;

    getline( f, line );

    for(int i = 1;i <= n; i++)
    {
        getline( f, line );

        istringstream is( line );

        while(is>>x)
            {
             if(i == 1)
                {
                    if(x <= k)
                        a[i][x] = x;
                }
             else
                {
                    if(x <= k)
                        for(int j = x;j <= k; j++)
                            if(a[i - 1][j - x])
                                a[i][j] = x;
                }
            }
    }

    construct(n, k);

    return 0;
}
