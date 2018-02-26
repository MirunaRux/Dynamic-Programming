#include <iostream>
#include <fstream>
using namespace std;

fstream f("date.in", ios :: in);
fstream g("date.out", ios :: out);

int max(int a, int b) /// functie care returneaza maximul dintre doua numere
{
    if(a > b)
        return a;
    else
        return b;
}

int min(int a, int b) /// functie care returneaza minimul dintre doua numere
{
    if(a < b)
        return a;
    else
        return b;
}

int main()
{
    int n;

    f>>n;

    int v[n + 1];

    for(int i = 0;i < n; i++)
        f>>v[i];

    f.close();

    /// cmax[i][j] = suma maxima care se poate obtine intre pozitia i si pozitia j (matricea se construieste pe diagonala
                                                                                    /// si pe paralele la diagonala)

    int cmax[n][n] = {0};
    int i, j, k, x, y, z;
    int s = 0;

    for(int i = 0; i < n; i++)
        s += v[i]; /// suma totala din vector

    for (k = 0; k < n; k++)
        for (i = 0, j = k; j < n; i++, j++)
        {
            /// x este valoarea lui cmax(i + 2, j)
            /// y este valoarea lui cmax(i + 1, j - 1)
            /// z este valoarea lui cmax(i, j - 2)
            x = ((i+2) <= j) ? cmax[i+2][j] : 0;
            y = ((i+1) <= (j-1)) ? cmax[i+1][j-1] : 0;
            z = (i <= (j-2))? cmax[i][j-2]: 0;

            cmax[i][j] = max(v[i] + min(x, y), v[j] + min(y, z));
                         ///(daca alege pc-ul v[i] + daca alege adversarul x sau y sau
                         /// daca alege pc-ul v[j] + daca aelge adversarul y sau z)
        }

    cout << 2*cmax[0][n-1] - s << '\n'; /// cu cat va fi mai mare suma calculatorului decat a adversarului

    int sum1 = 0, sum2 = 0;

    i = 0, j = n-1;

    bool myTurn = true;

    while (i <= j) /// simularea jocului
    {
        int P1 = cmax[i+1][j];
        int P2 = cmax[i][j-1];
        cout << (myTurn ? "I" : "You") << " take ";
        if (P1 <= P2)
        {
            cout << i+1 << " (" << v[i] << ")";
            i++;
        }
        else
        {
            cout << j+1 << " (" << v[j] << ")";
            j--;
        }
        cout << (myTurn ? ", " : ".\n");
        myTurn = !myTurn;
    }

    return 0;
}
