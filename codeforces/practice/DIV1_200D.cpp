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

const int NAX = 500000 + 5, MOD = 1000000007;

struct Node
{
    long long val;
    Node(long long one = 0) : val(one) {}
    Node operator+(const Node &rhs)
    {
        Node a = *this;
        a.val = max(a.val, rhs.val);
        return a;
    }
};
ostream &operator<<(ostream &out, const Node &p)
{
    out << p.val;
    return out;
}
istream &operator>>(istream &in, Node &p)
{
    in >> p.val;
    return in;
}

struct Segtree
{
    vector<Node> Seg, Lazy;
    vector<Node> Base;
    vector<bool> isLazy;
    int n;
    Segtree(int n = 2e5)
    {
        this->n = n;
        Seg.resize(4 * n + 10);
        Lazy.resize(4 * n + 10);
        isLazy.resize(4 * n + 10);
    }
    void merge(Node &curr, Node &l, Node &r)
    {
        curr = l + r;
    }
    void propagate(int node, int L, int R)
    {
        if (isLazy[node])
        {
            isLazy[node] = false;
            Seg[node] = Lazy[node];
            if (L != R)
            {
                Lazy[2 * node] = Lazy[node];
                Lazy[2 * node + 1] = Lazy[node];
                isLazy[2 * node] = true;
                isLazy[2 * node + 1] = true;
            }
            Lazy[node] = Node();
        }
    }
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            Seg[node] = Base[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
    }
    void build(vector<Node> &Arr)
    {
        Base = Arr;
        n = Arr.size();
        Seg.resize(4 * n + 10);
        Lazy.resize(4 * n + 10);
        isLazy.resize(4 * n + 10);
        build(1, 0, n - 1);
    }
    Node Query(int node, int start, int end, int qstart, int qend)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return Node();
        if (qstart <= start && end <= qend)
            return Seg[node];
        int mid = (start + end) / 2;
        Node l = Query(2 * node, start, mid, qstart, qend);
        Node r = Query(2 * node + 1, mid + 1, end, qstart, qend);
        Node ret;
        merge(ret, l, r);
        return ret;
    }
    Node qQuery(int node, int start, int end, int pos)
    {
        propagate(node, start, end);
        if (start == end)
            return Seg[node];
        int mid = (start + end) / 2;
        if (pos <= mid)
            return qQuery(2 * node, start, mid, pos);
        return qQuery(2 * node + 1, mid + 1, end, pos);
    }
    void Update(int node, int start, int end, int qstart, int qend, Node val)
    {
        propagate(node, start, end);
        if (qend < start || qstart > end || start > end)
            return;
        if (qstart <= start && end <= qend)
        {
            isLazy[node] = true;
            Lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        Update(2 * node, start, mid, qstart, qend, val);
        Update(2 * node + 1, mid + 1, end, qstart, qend, val);
        merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
    }
    void pUpdate(int node, int start, int end, int pos, Node val)
    {
        propagate(node, start, end);
        if (start == end)
        {
            isLazy[node] = true;
            Seg[node] = Node();
            Lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        if (pos <= mid)
            pUpdate(2 * node, start, mid, pos, val);
        else
            pUpdate(2 * node + 1, mid + 1, end, pos, val);
        merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
    }
    Node query(int pos)
    {
        return qQuery(1, 0, n - 1, pos);
    }
    Node query(int left, int right)
    {
        return Query(1, 0, n - 1, left, right);
    }
    void update(int pos, Node val)
    {
        pUpdate(1, 0, n - 1, pos, val);
    }
    void update(int start, int end, Node val)
    {
        Update(1, 0, n - 1, start, end, val);
    }
};

vector<int> adj[NAX];
int entry[NAX], ext[NAX], tim;

void dfs(int node, int par)
{
    entry[node] = ++tim;
    for (auto &child : adj[node])
        if (child != par)
            dfs(child, node);
    ext[node] = tim;
    db(node, entry[node], ext[node]);
}

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
        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(1, 1);
        int q;
        cin >> q;
        Segtree s(tim + 1);
        s.update(1, tim, Node(1));
        while (q--)
        {
            int c, v;
            cin >> c >> v;
            switch (c)
            {
            case 1:
                db(entry[v], ext[v], Node(0));
                s.update(entry[v], ext[v], Node(0));
#ifdef LOCAL
                for (int v = 1; v <= n; v++)
                    cout << s.query(v) << ' ';
                cout << '\n';
#else

#endif
                break;
            case 2:
                db(entry[v], Node(1));
                if (s.query(entry[v]).val == 0)
                    s.update(entry[v], Node(1));
#ifdef LOCAL
                for (int v = 1; v <= n; v++)
                    cout << s.query(v) << ' ';
                cout << '\n';
#else

#endif
                break;
            case 3:
                db(v, entry[v], ext[v], s.query(entry[v], ext[v]));
                cout << (s.query(entry[v], ext[v]).val == 0) << '\n';
                break;
            default:
                break;
            }
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
