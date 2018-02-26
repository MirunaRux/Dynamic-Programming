#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

void aliniereSecvente()
{
    string a, b;
    cin >> a >> b;
    int n = a.length(), m = b.length();
    vector <vector <int> > cost(n+1,vector<int>(m+1,0));

    int costSpatiu;
    cout << "costSpatiu = ";
    cin >> costSpatiu;

    int costDefault;
    cout << "cost Default Pt Litere Diferite = ";
    cin >> costDefault;
    vector <vector <int> > costAliniere(256, vector<int>(256, costDefault));
    for (int i = 0; i < 256; ++i) {
        costAliniere[i][i] = 0;
    }
    int nrCostSpeciale;
    cout << "nr costuri speciale = ";
    cin >> nrCostSpeciale;
    cout << "introduceti costuri speciale\n";
    for (int i = 0; i < nrCostSpeciale; ++i) {
        char a, b;
        int costAB;
        cin >> a >> b >> costAB;
        costAliniere[a][b] = costAB;
        costAliniere[b][a] = costAB;
    }

    for (int i = 1; i <= n; ++i) {
        cost[i][0] = cost[i - 1][0] + costSpatiu;
    }
    for (int i = 1; i <= m; ++i) {
        cost[0][i] = cost[0][i - 1] + costSpatiu;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cost[i][j] = cost[i - 1][j - 1] + costAliniere[a[i-1]][b[j-1]]; //cost aliniere 0 daca sunt egale sau costul penalizarii pt alinierea lor

            //verficam daca putem obtine un scor mai bun adaugand un spatiu in locul lui i sau j
            if (cost[i - 1][j] + costSpatiu < cost[i][j]) {
                cost[i][j] = cost[i - 1][j] + costSpatiu;
            }
            if (cost[i][j - 1] + costSpatiu < cost[i][j]) {
                cost[i][j] = cost[i][j - 1] + costSpatiu;
            }
        }

    cout << cost[n][m] <<"\n";

    //afisare rezultate
    int i = n;
    int j = m;
    string aSpatiat, bSpatiat;

    //reconstruim drumul parcurs in matrice in sens invers
    while (i > 0 && j > 0) {
        if (cost[i-1][j-1] + costAliniere[a[i-1]][b[j-1]] < cost[i][j-1] + costSpatiu && cost[i-1][j-1] + costAliniere[a[i - 1]][b[j - 1]] < cost[i-1][j] + costSpatiu) {
            aSpatiat = a[i - 1] + aSpatiat;
            bSpatiat = b[j - 1] + bSpatiat;
            i = i - 1;
            j = j - 1;
        }
        else {
            if (cost[i][j - 1] + costSpatiu < cost[i - 1][j] + costSpatiu) {
                aSpatiat = "-" + aSpatiat;
                bSpatiat = b[j - 1] + bSpatiat;
                j = j - 1;
            }
            else {
                aSpatiat = a[i - 1] + aSpatiat;
                bSpatiat = "-" + bSpatiat;
                i = i - 1;
            }
        }
    }
    cout << aSpatiat << "\n" << bSpatiat << "\n";
}

int main()
{
    aliniereSecvente();
    return 0;
}
