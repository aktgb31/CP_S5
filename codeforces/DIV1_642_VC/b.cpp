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

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a)
    {
        cin >> x;
        if (x < k)
            x = 0;
        else if (x == k)
            x = 1;
        else
            x = 2;
    }
    if (count(all(a), 1) == 0)
        cout << "no\n";
    else
    {
        if (n == 1)
        {
            cout << "yes\n";
            return;
        }
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = i + 1; j <= (i + 2) && j < n; j++)
            {
                if (a[i] && a[j])
                {
                    cout << "yes\n";
                    return;
                }
            }
        }
        cout << "no\n";
    }
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
