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

const int NAX = 3e5 + 5, MOD = 1000000007;

vector<pair<int, pair<int, int>>> q;
int n, m, a[NAX], mnvl[NAX], mxvl[NAX];
int st[4 * NAX], used[NAX];

<<<<<<< HEAD
// void update(int node, int l, int r, int pos, int val)
// {
//     if (l == r)
//     {
//         st[node] = val;
//         return;
//     }
//     int mid = ((ll)l + r) / 2;
//     if (pos <= mid)
//         update(2 * node, l, mid, pos, val);
//     else
//         update(2 * node + 1, mid + 1, r, pos, val);
//     st[node] = st[2 * node] + st[2 * node + 1];
// };

// int find(int node, int start, int end, int qstart, int qend)
// {
//     if (qend < start || qend < start || start > end)
//         return 0;
//     if (qstart <= start && end <= qend)
//         return st[node];
//     int mid = ((ll)start + end) / 2;
//     return find(2 * node, start, mid, qstart, qend) +
//            find(2 * node + 1, mid + 1, end, qstart, qend);
// };

=======
>>>>>>> ae0281531f0385f53aecdbe7901c4318c3025b80
void solveCase()
{
    cin >> n >> m;
    map<int, vector<int>> idv;
    ordered_set<int> s;
    for (size_t i = 1; i <= m; i++)
    {
        cin >> a[i];
        if (!idv.count(a[i]))
        {
            int sz = s.size();
            int sml = s.order_of_key(a[i]);
            sml = sz - sml;
            mxvl[a[i]] = sml + a[i];
        }
        s.insert(a[i]);
        idv[a[i]].pb(i);
    }
    for (size_t i = 1; i <= n; i++)
    {
        if (s.find(i) != s.end())
            mnvl[i] = 1;
        else
        {
            int sz = s.size();
            int sml = s.order_of_key(i);
            sml = sz - sml;
            mxvl[i] = i + sml;
            mnvl[i] = i;
        }
    }
    s.clear();
    for (int i = m; i >= 1; i--)
    {
<<<<<<< HEAD
        if (idv[a[i]].back() == i)
        {
            int sz = s.size();
            mxvl[a[i]] = max(mxvl[a[i]], sz + 1);
        }
        s.insert(a[i]);
    }
    for (auto &el : idv)
        for (size_t i = 0; i + 1 < el.s.size(); i++)
            q.pb({el.s[i], {el.s[i + 1], el.f}});
    sort(all(q), [](pair<int, pair<int, int>> A, pair<int, pair<int, int>> B) -> bool {
        if (A.s.f != B.s.f)
            return A.s.f < B.s.f;
        return A.f < B.f;
    });
    int j = 1;
    function<void(int, int, int, int, int)> update;
    function<int(int, int, int, int, int)> find;
    update = [&update](int node, int l, int r, int pos, int val) -> void {
        db("Update", node);
        if (l == r)
        {
            st[node] = val;
            return;
        }
        int mid = ((ll)l + r) / 2;
        if (pos <= mid)
            update(2 * node, l, mid, pos, val);
        else
            update(2 * node + 1, mid + 1, r, pos, val);
        st[node] = st[2 * node] + st[2 * node + 1];
    };
    find = [&find](int node, int start, int end, int qstart, int qend) -> int {
        db("Find", node, start, end, qstart, qend);
        if (qend < start || end < qstart || start > end)
            return 0;
        if (qstart <= start && end <= qend)
            return st[node];
        int mid = ((ll)start + end) / 2;
        return find(2 * node, start, mid, qstart, qend) +
               find(2 * node + 1, mid + 1, end, qstart, qend);
    };
    for (size_t i = 0; i < q.size(); i++)
    {
        while (j <= q[i].s.f)
        {
            if (!used[a[j]])
            {
                update(1, 1, m, j, 1);
                used[a[j]] = j;
            }
            else
            {
                update(1, 1, m, used[a[j]], 0);
                update(1, 1, m, j, 1);
                used[a[j]] = j;
            }
            ++j;
        }
        int diff = find(1, 1, m, q[i].f, q[i].s.f);
        mxvl[q[i].s.s] = max(mxvl[q[i].s.s], diff);
    }
    for (size_t i = 1; i <= n; i++)
        cout << mnvl[i] << ' ' << mxvl[i] << '\n';
=======
        if(idv[a[i]].back() == i)
        {
            int sz = s.size();
            mxvl[a[i]] = max(mxvla)
        }
        
    }
>>>>>>> ae0281531f0385f53aecdbe7901c4318c3025b80
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
