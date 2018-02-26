#include <fstream>
#include <iostream>

using namespace std;

int min(int a, int b, int c) /// functie care calculeaza minimul dintre 3 numere
{
    int vmin = a;
    if(b < vmin) vmin = b;
    if(c < vmin) vmin = c;

    return vmin;
}

int main()
{
    int i, j, k, m, n, **a, **lmax;

    ifstream fin("date.in");

    fin >> n >> m;

    a = new int*[n];
    lmax = new int*[n];
    for(i = 0; i < n; i++)
    {
        a[i] = new int[m];
        lmax[i] = new int[m];
    }

    for(i = 0; i < n; i++) /// citesc matricea
        for(j = 0; j < m; j++)
            fin >> a[i][j];

    fin >> k; /// citesc k

    fin.close();
    /// lmax[i][j] - retine latura maxima a unui patrat format din 0 cu coltul din dreapta jos de coord i si j
    for(i = 0; i < n; i++)
        lmax[i][0] = 1 - a[i][0]; /// calculez prima coloana din lmax

    for(j = 1; j < m; j++)
        lmax[0][j] = 1 - a[0][j]; /// calculez prima linie din lmax

    for(i = 1; i < n; i++)
        for(j = 1; j < m; j++)
            if(a[i][j] == 0)
                lmax[i][j] = min(lmax[i][j-1], lmax[i-1][j], lmax[i-1][j-1]) + 1; /// pt fiecare element din a = 0 -> lmax = minimul dintee vecini + 1
            else
                lmax[i][j] = 0; /// daca elementul din a = 1 -> lmax = 0

    int pmax = lmax[0][0];
    int imax = 0;
    int jmax = 0;

    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            if(pmax < lmax[i][j]) /// calculam maximul din matricea lmax
            {
                pmax = lmax[i][j]; /// calculam coordonatele punctului din dreapta jos
                imax = i;
                jmax = j;
            }

    ofstream fout("date.out");
    ///a)
    fout << pmax << endl << imax + 2 - pmax << " " << jmax + 2 - pmax << endl; /// afisam latura maxima si coordonatele punctului din stanga sus

    int nrPat = 0;

     for(int i = 0;i < n; i++)
         for(int j = 0;j < m; j++)
             if (lmax[i][j] >= k)
                nrPat += lmax[i][j] - k + 1; ///numarul de patrate cu latura maxim k si cu coltul din dreapta jos de coordonate i si j este dat de formula asta
    ///b)
    fout<<"Numarul de patrate de latura cel putin egala cu "<<k<<" este "<<nrPat<<endl;

    fout.close();

    return 0;
}
