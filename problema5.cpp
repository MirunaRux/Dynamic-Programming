#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define NMAX 100

using namespace std;

fstream f("date.in");

struct Activity
{
    int start, finish, profit;
};

int compare(Activity x, Activity y) ///functie care compara doua activitati dupa timpul de inceput
{
    return x.start < y.start;
}

int findSum(vector<Activity> arr) ///functie care calculeaza profitul total al activitatilor din arr
{
    int sum = 0;
    for (int i=0; i<arr.size(); i++)
        sum +=  arr[i].profit;
    return sum;
}

void findMaxProfit(vector<Activity> &arr)
{
    /// Sortam arr[] dupa timpul de inceput
    sort(arr.begin(), arr.end(), compare);

    /// A[i] retine activitatile optime act[0..i] ce se termina cu act[i]
    vector<vector<Activity> > A(arr.size());

    A[0].push_back(arr[0]);      /// A[0] primeste arr[0]

    for (int i=1; i<arr.size(); i++)
    {
        for (int j=0; j<i; j++)
        {
            /// A[i] = {MaxSum(A[j])} + arr[i], unde  j < i si arr[j].finish <= arr[i].start
            if ( (arr[j].finish <= arr[i].start) && (findSum(A[j]) > findSum(A[i])) )
                A[i] = A[j];
        }
        A[i].push_back(arr[i]);
    }

    vector<Activity> maxChain;

    /// gasim activitatile cu profitul maxim
    for (int i=0; i<A.size(); i++)
        if (findSum(A[i]) > findSum(maxChain))
            maxChain = A[i];
    cout<<"Profitul maxim: "<<findSum(maxChain)<<endl;
    cout<<"Activitatile: "<<endl;
    for (int i = 0; i < maxChain.size(); i++)
        cout << "(" <<  maxChain[i].start << ", " <<maxChain[i].finish <<") "<<endl;
}

int main()
{
    /*Activity a[] = { {1, 3, 1}, {2, 6, 8}, {4, 7, 2}, {10, 11, 5} };
    int n = sizeof(a) / sizeof(a[0]);*/
    int n;
    f>>n;

    Activity a[NMAX];
    for(int i=0; i<n; i++) ///citim activitatile
      {
        f>>a[i].start;
        f>>a[i].finish;
        f>>a[i].profit;
      }
    vector<Activity> arr(a, a + n); ///copiem activitatile in arr

    findMaxProfit(arr); ///calculam profitul maxim al activitatilor compatibile

    return 0;
}
