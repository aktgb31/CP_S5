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
    int n, k;
    cin >> n >> k;
    vector<int> poses(k);
    vector<int> tapHKya(n + 1);
    for (auto &x : poses)
    {
        cin >> x;
        tapHKya[x]++;
    }
    int res = 0;
    int lptr, rptr;
    lptr = rptr = 0;
    auto check = [&](int time) -> bool {
        auto copy = tapHKya;
        for (auto &x : poses)
            for (int j = x - time; j <= x + time; j++)
                if (1 <= j && j <= n)
                    copy[j] = 1;
        for (size_t i = 1; i <= n; i++)
            if (!copy[i])
                return false;
        return true;
    };
    for (size_t i = 0; i <= n; i++)
    {
        if (check(i))
        {
            res = i;
            break;
        }
    }
    cout << res + 1 << '\n';
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
