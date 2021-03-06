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

const int NAX = 2e5 + 5, MOD = 1000000007, max_N = 3e5 + 10, max_B = 1e3 + 10, B = 1e3;

ll T[max_B], X[max_B];
set<pair<int, int>> block[max_B];

void fix_up(int id)
{
    ll prev = id * B;
    ll x = 0;
    for (auto &knight : block[id])
    {
        if (knight.first > prev)
        {
            x += (knight.first - prev);
        }
        prev = max(prev + knight.second, (ll)knight.first + knight.second);
    }

    T[id] = prev;
    X[id] = x;
}

void insert(int t, int d)
{
    int id = t / B;
    block[id].insert({t, d});
    fix_up(id);
}

void remove(int t, int d)
{
    int id = t / B;
    block[id].erase({t, d});
    fix_up(id);
}

ll query(int t)
{
    int id = t / B;
    ll prev = 0;
    for (size_t i = 0; i < id; i++)
    {
        ll bstart = B * i;
        if (T[i] == 0)
            continue;
        if (prev > bstart + X[i])
            prev = T[i] + (prev - bstart - X[i]);
        else
            prev = T[i];
    }
    for (auto &k : block[id])
    {
        if (k.first > t)
            break;
        prev = max(prev + k.second, (ll)k.f + k.s);
    }
    return max(prev - t, 0LL);
}

void solveCase()
{
    int q;
    cin >> q;
    vector<int> ent(q + 1), dur(q + 1);
    for (size_t i = 1; i <= q; i++)
    {
        char type;
        cin >> type;
        if (type == '?')
        {
            int t;
            cin >> t;
            cout << query(t) << '\n';
        }
        else if (type == '+')
        {
            int t, d;
            cin >> t >> d;
            ent[i] = t, dur[i] = d;
            insert(t, d);
        }
        else
        {
            int id;
            cin >> id;
            remove(ent[id], dur[id]);
        }
    }
}

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
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}