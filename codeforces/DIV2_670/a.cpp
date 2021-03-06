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
    int n;
    cin >> n;
    vector<int> cnt(102);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int ptr1 = 0;
    vector<int> mex(2);
    for (size_t i = 0; i < 102; i++)
    {
        if (ptr1 == 0)
        {
            if (cnt[i] >= 2)
            {
            }
            else if (cnt[i] == 1)
            {
                mex[ptr1] = i;
                ptr1++;
            }
            else
            {
                mex[ptr1] = i;
                ptr1++;
                mex[ptr1] = i;
                ptr1++;
                break;
            }
        }
        else
        {
            if (cnt[i] >= 1)
            {
            }
            else if (cnt[i] == 0)
            {
                mex[ptr1] = i;
                ptr1++;
                break;
            }
        }
    }
    cout << mex[0] + mex[1] << '\n';
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
