#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;
int i, j, n, m, v[201][201], c[201][201];

void afisare(int a,int b)
{
    if(a==n && b==1)
    {
        return;
    }
    if(c[a][b-1]>c[a+1][b])
    {
        afisare(a,b-1);
        cout<<a<<" "<<b-1<<"\n";
    }
    else
    {
        afisare(a+1,b);
        cout<<a+1<<" "<<b<<"\n";
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>v[i][j];
        }
    }

    c[1][m]=v[1][m];
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            c[i+1][j]=max(c[i+1][j],c[i][j]+v[i+1][j]);
            c[i][j-1]=max(c[i][j-1],c[i][j]+v[i][j-1]);
        }
    }
    cout<<c[n][1]<<"\n";

    afisare(1,m);
    cout<<1<<" "<<m;

    return 0;
}
