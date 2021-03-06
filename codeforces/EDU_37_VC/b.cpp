// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<vector<int>> vecc;
    vector<int> res(n);
    for (size_t i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        vecc.pb({l, (int)i, r});
    }
    sort(all(vecc));
    int now = 1;
    for (size_t i = 0; i < n; i++)
    {
        if (now <= vecc[i][0])
        {
            now = vecc[i][0];
            res[vecc[i][1]] = now;
            now++;
        }
        else if (now <= vecc[i][2])
        {
            res[vecc[i][1]] = now;
            now++;
        }
    }
    for (auto &x : res)
    {
        cout << x << ' ';
    }
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
