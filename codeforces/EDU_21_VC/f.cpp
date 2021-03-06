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

using flowUnit = ll;
struct Edge
{
    int from, to;
    flowUnit cap, flow;
    int index;
    Edge(int from, int to, flowUnit cap, flowUnit flow, int index) : from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushReLabel
{
    int n;
    vector<vector<Edge>> g;
    vector<flowUnit> excess;
    vector<int> height, active, count;
    queue<int> Q;

    PushReLabel(int n) : n(n), g(n), excess(n), height(n), active(n), count(2 * n) {}

    void addEdge(int from, int to, flowUnit cap)
    {
        g[from].pb(Edge(from, to, cap, 0, g[to].size()));
        if (from == to)
            g[from].back().index++;
        g[to].pb(Edge(to, from, 0, 0, g[from].size() - 1));
    }

    void enqueue(int node)
    {
        if (!active[node] && excess[node] > 0)
        {
            active[node] = 0;
            Q.push(node);
        }
    }

    void push(Edge &e)
    {
        flowUnit amt = min(excess[e.from], e.cap - e.flow);
        if (height[e.from] <= height[e.to] || amt == 0)
            return;
        e.flow += amt;
        g[e.to][e.index].flow -= amt;
        excess[e.to] += amt;
        excess[e.from] -= amt;
        enqueue(e.to);
    }

    void relabel(int node)
    {
        count[height[node]]--;
        int d = 2 * n;
        for (auto &it : g[node])
            if (it.cap - it.flow > 0)
                d = min(d, height[it.to] + 1);
        height[node] = d;
        count[height[node]]++;
        enqueue(node);
    }

    void gap(int k)
    {
        for (int node = 0; node < n; node++)
        {
            if (height[node] < k)
                continue;
            count[height[node]]--;
            height[node] = max(height[node], n + 1);
            count[height[node]]++;
            enqueue(node);
        }
    }

    void discharge(int node)
    {
        for (size_t i = 0; excess[node] > 0 && i < g[node].size(); i++)
            push(g[node][i]);
        if (excess[node] > 0)
        {
            if (count[height[node]] == 1)
                gap(height[node]);
            else
                relabel(node);
        }
    }

    flowUnit max_flow(int source, int dest)
    {
        count[0] = n - 1;
        count[n] = 1;
        height[source] = n;
        active[source] = active[dest] = 1;
        for (auto &it : g[source])
        {
            excess[source] += it.cap;
            push(it);
        }
        while (Q.size())
        {
            auto node = Q.front();
            Q.pop();
            active[node] = false;
            discharge(node);
        }
        flowUnit max_flow = 0;
        for (auto &it : g[source])
            max_flow += it.flow;
        return max_flow;
    }
};

bool isPrime[2001];

void Solution::solveCase()
{
    fill(isPrime + 2, isPrime + 2001, 1);
    for (int i = 2; i < 2001; i++)
        if (isPrime[i])
            for (int j = i * i; j < 2001; j += i)
                isPrime[j] = false;

    int n, k;
    cin >> n >> k;

    vector<vector<ll>> a(n);
    for (auto &x : a)
    {
        int p, c, l;
        cin >> p >> c >> l;
        x = {p, c, l};
    }

    auto check = [&](int lvl) -> bool {
        vector<pair<ll, ll>> b;
        ll on = -1;
        for (auto &x : a)
        {
            if (x[2] > lvl)
                continue;
            if (x[1] == 1)
                on = max(on, x[0]);
            else
                b.pb({x[0], x[1]});
        }
        if (on > 0)
            b.pb({on, 1});

        int n = b.size();
        if (n == 0)
            return false;

        PushReLabel flow(n + 2);

        ll ans = 0;
        for (auto &x : b)
            ans += x.f;
        for (size_t i = 0; i < n; i++)
        {
            if (b[i].s % 2)
                flow.addEdge(n, i, b[i].f);
            else
                flow.addEdge(i, n + 1, b[i].f);
            for (size_t j = i + 1; j < n; j++)
                if (isPrime[b[i].s + b[j].s])
                    if (b[i].s % 2)
                        flow.addEdge(i, j, 1e9);
                    else
                        flow.addEdge(j, i, 1e9);
        }

        ans -= flow.max_flow(n, n + 1);
        db(lvl, ans, k);
        return ans >= k;
    };

    int low = 0, high = n + 2;
    int ans = high;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (check(mid))
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    if (ans > n)
        ans = -1;
    cout << ans << '\n';
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
