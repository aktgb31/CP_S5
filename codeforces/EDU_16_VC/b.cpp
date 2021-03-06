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
    void solveCase()
    {
        int n;
        cin >> n;
        ll sum = 0;
        vector<ll> y(n);
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            y[i] = x;
            sum += x;
        }
        // cout << sum << '\n';
        // return;
        ll suml = 0;
        ll minVal = 0;
        ll minCost = LLONG_MAX;
        sort(all(y));
        for (size_t i = 0; i < n; i++)
        {
            ll temp = i * y[i] - suml;
            temp += sum - (n - i) * y[i];
            sum -= y[i];
            suml += y[i];
            db(i, temp, minCost, minVal);
            if (temp <= minCost)
            {
                if (temp == minCost)
                    minVal = min(minVal, y[i]);
                else
                    minVal = y[i];
                minCost = temp;
            }
        }
        cout << minVal << '\n';
    }
};

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
