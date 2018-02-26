#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

struct cub
{
    int lungime;
    int culoare;
    bool operator < (const cub& other)
    {
        return lungime < other.lungime;
    }
};

void cuburi()
{
    int n, p;
    cin >> n >> p;

    vector <cub> cuburi(n+1);

    cuburi[0].lungime = -1; ///ne luam un cub care poate veni deasupra la orice
    cuburi[0].culoare = -1;

    for (int i = 1; i <= n; ++i) ///citim cele n cuburi
    {
        cin >> cuburi[i].lungime;
        cin >> cuburi[i].culoare;
    }

    vector <int> inaltimeMax(n+1,0); ///inaltimea maxima a unui turn din cuburile 1...i

    vector <int> pred(n+1, -1); ///predecesorul cubului i in cel mai bun turn in care apare

    vector <int> nrTurnuri(n+1, 0); ///nr de turnuri maxime care se pot forma din cuburile 1...i

    nrTurnuri[0] = 1;

    inaltimeMax[0] = 0;

    ///sortam crescator
    ///nu conteaza directia in care construim turnul (jos sus / sus jos)
    /// sus jos e mai bn pt predecesori
    sort(cuburi.begin(), cuburi.end());

    ///pt fiecare cub de la 1 la i
    for (int i = 1; i <= n; ++i)
    {
        /// parcurgem in spate toate turnurile la care putem sa-l alipim (inclusiv turnul vid)
        for (int j = i - 1; j >= 0; --j)
            {
                ///si il alipim la turnul cel mai bun
            if (cuburi[j].culoare != cuburi[i].culoare && cuburi[j].lungime < cuburi[i].lungime)
            {
                if (inaltimeMax[j] + cuburi[i].lungime > inaltimeMax[i])
                {
                    inaltimeMax[i] = inaltimeMax[j] + cuburi[i].lungime;
                    pred[i] = j;
                    nrTurnuri[i] = nrTurnuri[j];
                }
                ///in caz de egalitate luam in considerare nr de moduri in care se poate forma cel mai bun turn
                else
                {
                    if (inaltimeMax[j] + cuburi[i].lungime == inaltimeMax[i])
                    {
                        nrTurnuri[i] += nrTurnuri[j];
                    }
                }
            }
            }
    }

    cout << "\n\n";

    int i = n;

    while (i > 0 && pred[i] == -1)
    {
        --i;
    }

    for (; i > 0; i = pred[i])
    {
        cout << cuburi[i].lungime <<" " << cuburi[i].culoare <<"\n";
    }

    cout << nrTurnuri[n] <<"\n";
}
int main()
{
    cuburi();

    return 0;
}
