#include <iostream>
#include<stdio.h>
#include<limits.h>
#include <vector>
#include <fstream>
#define R 100
#define C 100

using namespace std;
fstream f("date.in");

int maxm(int x, int y);

int tc[R][C];

int maxCost(int cost[R][C], int m, int n) ///functie care calculeaza valoarea maxima a drumului
{
     int i, j;

     tc[0][0] = cost[0][0]; /// plecam din patratica de coordonate (0,0)

     for (i = 1; i <= m; i++) ///calculam costurile drumurilor pana la fiecare patratica de pe prima coloana
        tc[i][0] = tc[i-1][0] + cost[i][0];

     for (j = 1; j <= n; j++) ///calculam costurile drumurilor pana la fiecare patratica de pe prima linie
        tc[0][j] = tc[0][j-1] + cost[0][j];

     for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++) ///pentru restul patratelelor cosrul drumului pana la ele este
            tc[i][j] = maxm(tc[i-1][j], tc[i][j-1]) + cost[i][j]; ///maximul dintre costurile drumurilor pana la patratelele vecine(sus sau stanga)
                                                                  ///+ costul patratelei curente

     return tc[m][n];
}

int maxm(int x, int y) ///functie care calculeaza maximul dintee doua numere
{
   if (x > y)
      return x;
   else
      return y ;
}

int main()
{
   int m, n;
   f>>m;
   f>>n;

   int cost[R][C];
   for(int i = 0;i < m; i++) ///citim matricea
   for(int j = 0;j < n; j++)
      f>>cost[i][j];

   cout<<maxCost(cost, m - 1, n - 1)<<endl; ///afisam costul maxim al drumului

   ///refacem drumul
   vector<pair<int, int> > drum; ///retinem coordonatele patratelelor care formaza drumul de lungime maxima

   pair<int, int> x;
   int i = n - 1; ///plecam de la patratica de finish (patratica de coordonate n-1, m-1)
   int j = m - 1;

    while(i != -1 && j != -1) ///incercam sa ajungem la patratica de start (de coordonate 0, 0)
    {
        x.first = i + 1; x.second = j + 1; ///adaugam in drum patratica aleasa la pasul anterior

        drum.push_back(x);

        int temp;

        if(i == 0)  j--; ///daca suntem pe prima linie a matricei ne putem deplasa doar la stanga(j--)
        else
            if(j == 0)  i--; ///daca suntem pe prima coloana a matricei ne putem deplasa doar in sus(i--)
            else ///altfel
              { temp = maxm(tc[i - 1][j], tc[i][j - 1]); ///alegem maximul dintre valorile patratelelor vecine (stanga sau sus)
                if(temp == tc[i - 1][j]) i--; ///daca am ales patratica de mai sus ne deplasam o patratica in sus
                else j--; ///daca am ales patratica de la dreapta ne deplasam la stanga cu o patratica
              }
    }

    for(i = drum.size() - 1; i >= 0; i--)
       cout<<drum[i].first<<" "<<drum[i].second<<endl;

   return 0;
}
