#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

void dictionarAfisareRec(int i, string & cod, vector <int> & pred)
{
    if (pred[i] < 0)
    {
        for (int j = 0; j <= i; ++j) {
            cout << cod[j];
        }
        return;
    }
    dictionarAfisareRec(pred[i], cod, pred);
    cout << "+";
    for (int j = pred[i]+1; j <= i; ++j) {
        cout << cod[j];
    }
}


void dictionar() {
    int n;
    cin >> n;

    ///folosim un map pt a stii ce cuvinte apartin dictionarului
    ///cuvinte[string] = true daca apartine, false daca nu apartine
    unordered_map <string, bool> cuvinte;
    cuvinte["0"] = true;
    cuvinte["1"] = true;

    ///citim cuvinte
    for (int i = 2; i < n + 2; ++i)
    {
        string cuvantCurent;
        cin >> cuvantCurent;
        cuvinte[cuvantCurent] = true;
    }

    ///citim codul
    string cod;
    cin >> cod;
    int m = cod.length();

    vector <int> nrMinCuv(m+1,INT_MAX); /// nr minim de cuvinte din care putem forma codul 0...i
    vector <int> pred(m, -1); /// unde incepe cuvantul curent si se termina cuvantul precedent folosit

    nrMinCuv[0] = 0;

    ///pt fiecare litera noua
    for (int i = 0; i < m; ++i)
    {
        ///parcurgem in spate toate posibilele cuvinte
        string cuvCurent = "";
        for (int j = i - 1; j >= -1; --j)
        {
            cuvCurent = cod[j+1] + cuvCurent;
            ///daca gasim in dictionar cuvantul curent
            if (cuvinte[cuvCurent])
                ///verificam daca folosindu-l ni se imbunatateste nr de cuvinte minime
                if (nrMinCuv[j+1] + 1 < nrMinCuv[i+1])
                {
                    nrMinCuv[i+1] = nrMinCuv[j+1] + 1;
                    pred[i] = j;
                }
        }
    }

    ///afisam recursiv cuvintele alese (pt a aprea in ordinea de la stanga la dreapta / in oridnea alegerii)
    dictionarAfisareRec(m-1, cod, pred);
    cout << "\n\n";
}
int main()
{
    dictionar();
    return 0;
}
