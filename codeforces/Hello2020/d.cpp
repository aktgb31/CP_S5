// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
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
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    vector<pair<int, int>> order1;
    vector<pair<int, int>> order2;
    vector<int> aa;
    for (int i = 0; i < n; ++i)
    {
        aa.pb(i);
        int x, y;
        cin >> x >> y;
        order1.pb({x, y});
        cin >> x >> y;
        order2.pb({x, y});
    }
    Random<int> r(0, 1);
    Random<int> R(1, n);
    srand(time(NULL));
    while ((chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count()) < 1.9)
    {
        vector<pair<int, pair<int, int>>> sel;
        vector<pair<int, pair<int, int>>> sel2;
        int len = R(rng);
        random_shuffle(all(aa));
        for (int i = 0; i < n; ++i)
        {
            if (r(rng))
            {
                sel.pb({order1[aa[i]].f, {0, aa[i]}});
                sel.pb({order1[aa[i]].s, {1, aa[i]}});
                sel2.pb({order2[aa[i]].f, {0, aa[i]}});
                sel2.pb({order2[aa[i]].s, {1, aa[i]}});
            }
            if (sel.size() == len)
                break;
        }
        sort(all(sel));
        sort(all(sel2));
        pc(sel, sel2);
        int curr = -1;
        bool ok1, ok2;
        ok1 = ok2 = true;
        for (int i = 0; i < sel.size(); ++i)
            if (sel[i].s.f == 0)
            {
                if (curr == -1)
                {
                    curr = sel[i].s.s;
                }
                else
                {
                    ok1 = false;
                    break;
                }
            }
            else
            {
                if (curr == -1)
                {
                    ok1 = false;
                    break;
                }
                else
                {
                    if (curr == sel[i].s.s)
                        ;
                    else
                    {
                        ok1 = false;
                        break;
                    }
                    curr = -1;
                }
            }
        curr = -1;
        for (int i = 0; i < sel2.size(); ++i)
            if (sel2[i].s.f == 0)
            {
                if (curr == -1)
                {
                    curr = sel2[i].s.s;
                }
                else
                {
                    ok2 = false;
                    break;
                }
            }
            else
            {
                if (curr == -1)
                {
                    ok2 = false;
                    break;
                }
                else
                {
                    if (curr == sel2[i].s.s)
                        ;
                    else
                    {
                        ok2 = false;
                        break;
                    }
                    curr = -1;
                }
            }
        db(ok1, ok2);
        if (ok1 != ok2)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i)
    {
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
