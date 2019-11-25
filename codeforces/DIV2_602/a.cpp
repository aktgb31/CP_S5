//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
#ifdef LOCAL
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " { ";
    for (const auto &v : arg1)
        cerr << v << ' ';
    cerr << " }\n";
    PC(comma, args...);
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
#else
#define db(...)
#define pc(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10, mod = 1000000007;

void solve(int caseNo)
{
    int n, minx, maxx, x;
    cin >> n;
    vector<pair<int, int>> V(n);
    minx = mod, maxx = -1;
    for (int i = 0; i < n; ++i)
        cin >> V[i].f >> V[i].s;
    if (n == 1)
    {
        cout << 0 << '\n';
        return;
    }
    sort(V.begin(), V.end());
    pc(V);
    int maxlx = V[0].s;
    for (int i = 0; i < n; ++i)
        if (V[i].f <= maxlx)
            maxlx = min(maxlx,V[i].s);
        else break;
    int minrx = V[n-1].f;
    for (int i = n-1; i >= 0; --i)
        if (maxlx <= V[i].s)
            minrx = max(minrx,V[i].f);
        else break;
    db(maxlx,minrx);
    cout <<  max(0,minrx - maxlx) << '\n';
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef multitest
    cin >> t;
#endif
    for (int i = 0; i < t; ++i)
        solve(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}