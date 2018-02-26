#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

int C[100], T[100];
bool P[100][100];
char s[100];

void solutie(int i) /// functie care afiseaza solutia de la stg la dr recursiv
{
    if(i != -1)
    {
        solutie(T[i]);
        for(int j = T[i]+1; j <= i; j++)
            cout << s[j];
        cout << endl;
    }
}


int main()
{
    int i, j, n, ls;

    cout << "Cuvantul: ";
    cin >> s;

    n = strlen(s);

    /// P[i][j] = true daca de la pozitia i si pana la j in sir avem un palindrom si false altfel

    for (i = 0; i < n; i++)
        P[i][i] = true; /// diagonala este true deoarece o litera este palindrom

    for (ls = 2; ls <= n; ls++) /// ls = lungimea unui posibil palindrom
        for (i = 0; i < n - ls + 1; i++)
        {
            j = i + ls - 1;

            if (ls == 2) /// cazul palindroamelor de 2 litere
                P[i][j] = (s[i] == s[j]);
            else
                P[i][j] = (s[i] == s[j]) && P[i+1][j-1]; /// altfel
        }

    int nrp = 0;
    for (i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            nrp = nrp + P[i][j]; ///numaram cate palindroame am gasit
    /// a)
    cout << "Numar de palindromuri din sir: " << nrp << endl;

    /// C[i] - nr minim de palindromuri in care poate fi spart subsirul s[0], s[1], ... s[i]
    /// T[i] - pozitia dupa care au efectuat taietura pt a obtine minim din C[i]

    C[0] = 0;
    T[0] = -1;
    for(i = 1; i < n; i++)
        if(P[0][i])
        {
            C[i] = 0;
            T[i] = -1;
        }

        else
        {
            C[i] = INT_MAX;
            T[i] = -1;
            for(j = 0; j < i; j++)
                if(P[j+1][i] && (C[i] > C[j] + 1))
                {
                    C[i] = C[j] + 1;
                    T[i] = j;
                }
        }

    ///b)
    cout << "Numarul minim de palindromuri: " << C[n-1] + 1 << endl;

    i = n - 1;
    while(i >= 0) /// construirea palindroamelor din descompunere de la ultimul la primul
    {
        for(j = T[i]+1; j <= i; j++)
            cout << s[j];
        cout << endl;
        i = T[i];
    }

    cout << "Descompunerea: " << endl; /// afisarea palindroamelor
    solutie(n-1);

    return 0;
}
