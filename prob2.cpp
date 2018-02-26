#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

fstream f("date.in", ios :: in);
fstream g("date.out", ios :: out);

const int NMAX = 100;

int n, m, table[NMAX][NMAX], smax[NMAX][NMAX];

void citire()
{
    f>>n>>m;

    for(int i = 1; i <= n ; i++)
        for(int j = 1; j <= m; j++)
            f>>table[i][j];

    f.close();
}

int max(int a, int b, int c)
{
    int vmax = a;
    if(b > vmax) vmax = b;
    if(c > vmax) vmax = c;

    return vmax;
}

int verif(int i, int j)
{
    if(i > n || i < 1)
        return INT_MIN;
    else
        return smax[i][j];
}

///functia intoarce acum linia pe care se afla maximul, deoarece am nevoie de ea cand reconstitui solutia
int determinare_maxim()
{
    for(int i = 1; i <= n; i++)
        smax[i][m] = table[i][m];

    ///matricea smax se completeaza pe coloane
    for(int j = m - 1; j >= 1; j--)
        for(int i = 1; i <= n; i++)
            smax[i][j] = table[i][j] + max(verif(i - 1, j + 1), verif(i, j + 1), verif(i + 1, j + 1));

    int maxx = smax[1][1];
    int lmax = 1;

    for(int i = 1; i <= n; i++)
        if(maxx < smax[i][1])
        {
            maxx = smax[i][1];
            lmax = i;
        }

    return lmax;
}

int coord_max(int i, int j, int &lin)
{
    ///functia intoarce numarul aparitiilor maximului intre cele 3 valori vecine, ca sa vezi daca solutia este unica sau nu
    int k = 0;
    if(smax[i - 1][j + 1] == max(smax[i - 1][j + 1], smax[i][j + 1], smax[i + 1][j + 1]))
        lin = i - 1, k++;

    if(smax[i][j + 1] == max(smax[i - 1][j + 1], smax[i][j + 1], smax[i + 1][j + 1]))
        lin = i, k++;

    if(smax[i + 1][j + 1] == max(smax[i - 1][j + 1], smax[i][j + 1], smax[i + 1][j + 1]))
        lin = i + 1, k++;

    return k;
}

///gasirea unui drum optim este mult mai simpla si nu necesita recursivitate neaparat
///practic, la fiecare pas, selectez linia de unde a fost selectat maximul in calculul lui smax
void drum_optim(int pmax)
{
    int lcrt = pmax;
    bool sol_unica = true;

    for(int i = 1; i < m; i++)
    {
        g << lcrt << " " << i << endl;

        int k = coord_max(lcrt, i, lcrt);
        if(k != 1)
            sol_unica = false;
    }

    ///pentru ultima coloana nu mai calculez succesorul
    g << lcrt << " " << m << endl;

    g << (sol_unica ? "Traseul optim este unic" : "Traseul optim nu este unic");
    g.close();
}

int main()
{
    citire();

    int pmax = determinare_maxim();

    ///maximul se gaseste pe linia pmax a primei coloane din smax
    g << smax[pmax][1]<<'\n';
    drum_optim(pmax);
    g.close();

    return 0;
}

