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
    string str;
    cin >> str;
    if (count(all(str), '(') == count(all(str), ')'))
    {
        int res = 0;
        int cnt = 0;
        int i = 0;
        while (i < n)
        {
            int j = i + 1;
            bool ok = true;
            cnt = 0;
            if (str[i] == '(')
                cnt++;
            else
                cnt--;
            ok = ok && cnt >= 0;
            while (j < n && cnt)
            {
                if (str[j] == '(')
                    cnt++;
                else
                    cnt--;
                ok = ok && cnt >= 0;
                ++j;
            }
            if (!ok)
                res += j - i;
            i = j;
        }
        cout << res << '\n';
    }
    else
    {
        cout << -1 << '\n';
        return;
    }
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
