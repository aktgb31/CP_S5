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
        vector<int> a(n);
        set<int> l, r;
        for (auto &x : a)
        {
            cin >> x;
            r.insert(x);
        }
        if (is_sorted(all(a)))
            cout << "NO\n";
        else
        {
            db("stage2");
            for (size_t i = 0; i < n; i++)
            {
                r.erase(a[i]);
                auto itr = r.lower_bound(a[i]);
                if (itr != r.begin())
                {
                    --itr;
                    auto itl = l.lower_bound(a[i]);
                    if (itl != l.begin())
                    {
                        itl--;
                        cout << "YES\n";
                        cout << find(all(a), *itl) - a.begin() + 1 << ' ';
                        cout << i + 1 << ' ';
                        cout << find(all(a), *itr) - a.begin() + 1 << '\n';
                        return;
                    }
                }
                l.insert(a[i]);
            }
            cout << "NO\n";
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
