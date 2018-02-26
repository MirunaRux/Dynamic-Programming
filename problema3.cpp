#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
fstream f("date.in");

int min(int x, int y, int z)
{
    return min(min(x, y), z);
}

int dp[100][100];

int editDistDP(string str1, string str2, int n, int m, int c1, int c2, int c3)
{
    for (int i=0; i<=n; i++)    /// populam dp[][]
    {
        for (int j=0; j<=m; j++)
        {
             if (i==0)         /// Daca primul sir e vid, inseram toate caracterele sirului 2
                dp[i][j] = j;  /// Nr. minim operatii = j

            else if (j==0)   /// Daca al doilea sir e vid, inseram toate caracterele sirului 1
                dp[i][j] = i; /// Nr. minim operatii = i

            else        ///daca ultimele caractere coincid, va primi aceeasi valoare
               if (str1[i-1] == str2[j-1])
                       dp[i][j] = dp[i-1][j-1];

            /// daca ultimele caractere difera, consideram posibilitatile
               else
                {
                    int temp = min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]);
                    if(temp == dp[i][j-1])     /// Inserare
                         dp[i][j] = c1 + temp;
                    else
                      if(temp == dp[i-1][j])   ///Stergere
                         dp[i][j] = c2 + temp;
                      else
                        dp[i][j] = c3 + temp;   ///Substitutie
                }
        }
    }
    return dp[n][m];
}

int main()
{
    string str1,str2;
    int c1, c2, c3;   ///c1 pt inserare, c2 pt stergere, c3 pt substitutie

    f>>str1>>str2;
    f>>c1>>c2>>c3;

    int n = str1.length();
    int m = str2.length();

    cout << editDistDP(str1, str2, n, m, c1, c2, c3)<<endl;

    ///refacem drumul
    vector< pair<string, string> > drum; ///retinem oparatia pe care am facut-o si litera asupra careia am facut operatia

    pair<string, string> x;

    int i = n;
    int j = m;

    while(i!=0 || j!=0)
    {
        int temp;
        if(j==0) { x.first = "stergere";   x.second = str1[j];
                   drum.push_back(x);
                  i--;
              }
        else
        {
          temp = min(dp[i-1][j-1], dp[i][j-1], dp[i-1][j]);
          if(temp == dp[i-1][j-1])
             {
                if(dp[i-1][j-1]==dp[i][j])
                     { x.first = "pastram";   x.second = str1[i-1];
                       drum.push_back(x);
                     }
                else
                   if(dp[i-1][j-1]+1==dp[i][j])
                     {  x.first = "substitutie";
                        x.second = str1[i-1]; x.second += "-"; x.second += str2[j-1];
                        drum.push_back(x);
                     }
                i--; j--;
             }

          else
            if(temp == dp[i-1][j])
            {   x.first = "stergere";   x.second =str1[i-1];
                drum.push_back(x);
                i--;
            }
            else
                if(temp == dp[i][j-1])
                 { x.first = "insertie";   x.second = str2[j-1];
                   drum.push_back(x);
                   j--;
                 }
        }
    }
    for(int i = drum.size()-1; i>=0; i--)
        cout<<drum[i].first<<" "<<drum[i].second<<endl;

    return 0;
}
