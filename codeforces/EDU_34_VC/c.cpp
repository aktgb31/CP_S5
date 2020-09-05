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

// int cnt[NAX];
void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<int> vecc(n);
    for (auto &x : vecc)
        cin >> x;
    sort(all(vecc));
    int lptr = 0, rptr = 0;
    int cnt = 0;
    while (rptr < n)
        if (lptr < rptr && vecc[lptr] < vecc[rptr])
        {
            ++lptr;
            ++rptr;
        }
        else
            ++rptr;
    // cout << lptr << ' ' << rptr << '\n';
    cout << rptr - lptr << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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
