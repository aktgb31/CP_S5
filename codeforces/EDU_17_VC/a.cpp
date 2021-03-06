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
        ll n, k;
        cin >> n >> k;
        vector<ll> divisors;
        for (ll i = 1; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                if (n == i * i)
                    divisors.pb(i);
                else
                {
                    divisors.pb(i);
                    divisors.pb(n / i);
                }
            }
        }
        sort(all(divisors));
        if (k > divisors.size())
            cout << -1 << '\n';
        else
        {
            cout << divisors[k - 1] << '\n';
        }
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
