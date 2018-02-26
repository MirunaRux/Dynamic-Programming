#include <iostream>
#include <fstream>
#include <vector>
#define NMAX 100

using namespace std;

fstream f("date.in");

struct Pair
{
    int a;
    int b;
};

void maxChainLength(vector<Pair> &arr, int n)
{
    /// L[i] memoreaza cel mai lung lant format din piesele arr[0..i] ce au ca ultima piesa arr[i].
    vector<vector<Pair> > L(arr.size());

    L[0].push_back(arr[0]);   /// L[0] primeste arr[0]

    for (int i = 1; i < arr.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            /// L[i] = {Max(L[j])} + arr[i]
            if ((arr[j].b == arr[i].a) && (L[j].size() > L[i].size()))
                L[i] = L[j];
        }
        L[i].push_back(arr[i]);
    }

    /// afisarea lantului de lungime maxima si a nr de posibilitati
    vector<Pair> maxChain;
    maxChain=L[0];
    int nr=1; ///numara cate siruri de lungime maxima exista
    for(int i=1; i<n; i++)
    {
        if (L[i].size() > maxChain.size()) ///daca gasim un sir de lungime mai mare
             { maxChain = L[i]; ///il retinem
               nr = 1; ///reinitializam numarul de siruri de lungime maxima cu 1
             }
        else
            if (L[i].size() == maxChain.size()) ///daca gasim siruri de lungime egala cu lungimea maxima
                 nr++; ///le numaram
    }
    for(int i=0; i<maxChain.size(); i++) ///afisam ultimul subsir de lungime maxima pe care l-am retinut
        cout<<maxChain[i].a<<" "<<maxChain[i].b<<endl;
    cout<<"Nr. de posibilitati: "<<nr; ///si numarul de subsiruri de lungime maxima care se gasesc in vectorul dat
}

int main()
{
    /*Pair a[] = {{1, 8}, {1, 5}, {5, 3}, {5, 2}, {4, 8}, {2, 4}, {2, 3}};
    int n = sizeof(a)/sizeof(a[0]);*/

    int n;
    f>>n;

    Pair a[NMAX]; ///cele n perechi de numere
    for(int i=0; i<n; i++)
      {
        f>>a[i].a;
        f>>a[i].b;
      }

    vector<Pair> arr(a, a+n); ///copiez in arr pe a
    /*for(int i=0; i<n; i++)
        arr[i] = a[i];*/
    maxChainLength(arr , n);

    return 0;
}
