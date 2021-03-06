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

class Solution
{
    using u64 = uint64_t;
    using u128 = uint64_t;

    u64 binaryPower(u64 base, u64 e, u64 mod)
    {
        u64 result = 1;
        base %= mod;
        while (e)
        {
            if (e & 1)
                result = (u128)result * base % mod;
            base = (u128)base * base % mod;
            e >>= 1;
        }
        return result;
    }

    bool checkComposite(u64 n, u64 a, u64 d, int s)
    {
        u64 x = binaryPower(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        auto xCopy = x;
        for (int r = 1; r < s; ++r)
        {
            x = (u128)x * x % n;
            if (x == n - 1)
                return false;
        }
        return true;
    }

    bool MillerRabin(u64 n)
    {
        const int iter = 16;
        if (n < 4)
            return n == 2 || n == 3;
        int s = 0;
        u64 d = n - 1;
        while ((d & 1) == 0)
        {
            d >>= 1;
            s++;
        }
        for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        {
            if (n == a)
                return true;
            if (checkComposite(n, a, d, s))
                return false;
        }
        return true;
    }

private:
    int n, m, k;
    int xorExpo(int base, int idx)
    {
        if (idx & 1)
            return base;
        return 0;
    }
    map<int, int> dp;
    int getGrundy(int logLen)
    {
        if (dp.count(logLen))
            return dp[logLen];
        int &ret = dp[logLen];
        if (logLen < k || logLen == 1)
            ret = 0;
        else
        {
            vector<int> vec;
            if (MillerRabin(logLen))
            {
                int i = 1;
                if (i != logLen)
                    if (i >= k)
                        vec.pb(xorExpo(getGrundy(i), logLen / i));
                if (i != 1)
                    if (logLen / i >= k)
                        vec.pb(xorExpo(getGrundy(logLen / i), i));
            }
            else
            {
                for (ll i = 1; i * i <= logLen; i++)
                    if (logLen % i == 0)
                    {
                        if (i != logLen)
                            if (i >= k)
                                vec.pb(xorExpo(getGrundy(i), logLen / i));
                        if (i != 1)
                            if (logLen / i >= k)
                                vec.pb(xorExpo(getGrundy(logLen / i), i));
                    }
            }
            db(logLen);
            sort(all(vec));
            pc(vec);
            vec.erase(unique(all(vec)), vec.end());
            ret = 0;
            pc(vec);
            for (size_t i = 0; i < vec.size(); i++)
                if (vec[i] == ret)
                    ret++;
                else
                    break;
        }
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> m >> k;
        if (xorExpo(getGrundy(m), n) == 0)
            cout << "Marsel\n";
        else
            cout << "Timur\n";
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