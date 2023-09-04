#include <bits/stdc++.h>
#include <cstdlib>
#define INF 999999
using namespace std;

int main()
{
    // int n = 300;
    cout << 1 << endl;
    // cout << n / 10 << endl;
    // for (int k = 2; k <= n;k++){
    //     if(k % 10 != 0)
    //         continue;
    int k = 1000;
    vector<vector<int>> ans(k, vector<int>(k));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (i != j)
                ans[i][j] = rand() % 10;
        }
        }
        cout << k << " " << 1 << endl;
        for (auto i : ans)
        {
            for (auto j : i)
                cout << j << " ";
            cout << endl;
        }
    // }
    return 0;
}