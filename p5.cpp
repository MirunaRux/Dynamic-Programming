#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

struct activitate
{
    int indice;
    int profit=0;
    int deadline=0;
    int durata=0;
    bool operator<(activitate other)
    {
        return deadline < other.deadline;
    }
};

void spectacole() {
    int n;
    cin >> n;
    vector <activitate> activitati(n+1);

    for (int i = 1; i <= n; ++i)
    {
        activitati[i].indice = i;
        cin >> activitati[i].profit;
        cin >> activitati[i].deadline;
        cin >> activitati[i].durata;
    }

    sort(activitati.begin(), activitati.end()); /// sortam activitatile dupa deadline

    vector <vector <int> > profit(n + 1, vector<int>(activitati[n].deadline + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int d=1; d <= activitati[i].deadline; ++d)
        {
            profit[i][d] = profit[i - 1][d];
            if (d - activitati[i].durata >= 0)
            {
                if (profit[i - 1][d - activitati[i].durata] + activitati[i].profit > profit[i][d])
                    profit[i][d] = profit[i - 1][d - activitati[i].durata] + activitati[i].profit;
            }
        }
        for (int d = activitati[i].deadline + 1; d <= activitati[n].deadline; ++d)
            profit[i][d] = profit[i][d - 1];
    }

    cout << profit[n][activitati[n].deadline] << "\n";

    //afisare
    int i = n;
    int d = activitati[n].deadline;
    set <int> activitatiSelectate;
    while (i>=1) {
        if (d - activitati[i].durata >= 0) {
            if (profit[i - 1][d - activitati[i].durata] + activitati[i].profit > profit[i - 1][d]) {
                activitatiSelectate.insert(activitati[i].indice);
                d = activitati[i].deadline - activitati[i].durata;
            }
        }
        i -= 1;
    }
    set<int>::iterator it;
    for (it=activitatiSelectate.begin();it!=activitatiSelectate.end();it++)
        cout << *it << " ";
    cout << "\n";
}

int main()
{
    spectacole();
    return 0;
}
