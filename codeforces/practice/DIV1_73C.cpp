// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;
#define int long long

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<int> d(n + 2, 0);
        vector<int> u(n + 2, 0);
        for (size_t i = 2; i <= n; i++)
        {
            int k = 2;
            while (true)
            {
                int x = i - (k * (k - 1)) / 2;
                if (x < 0)
                    break;
                if (x % k == 0)
                {
                    x /= k;
                    int t = 0;
                    for (size_t j = 0; j < k; j++)
                        t ^= d[x + j];
                    u[t] = i;
                }
                ++k;
            }
            int r = 0;
            while (u[r] == i)
                ++r;
            d[i] = r;
            db(i, r);
        }
        if (d[n] == 0)
            cout << -1 << '\n';
        else
        {
            int k = 2;
            while (true)
            {
                int x = n - (k * (k - 1) / 2);
                if (x % k == 0)
                {
                    x /= k;
                    int t = 0;
                    for (size_t j = 0; j < k; j++)
                        t ^= d[x + j];
                    if (t == 0)
                        break;
                }
                ++k;
            }
            cout << k << '\n';
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
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}