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

class UnionFind
{ // OOP style
private:
    vector<int> p, rank, setSize; // remember: vi is vector<int>
    int numSets;

public:
    UnionFind(int N)
    {
        setSize.assign(N, 1);
        numSets = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    bool unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y])
            {
                p[y] = x;
                setSize[x] += setSize[y];
            }
            else
            {
                p[x] = y;
                setSize[y] += setSize[x];
                if (rank[x] == rank[y])
                    rank[y]++;
            }
            return true;
        }
        return false;
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

void Solution::solveCase()
{
    int n;
    cin >> n;
    set<int> adj[n + 1];
    for (size_t i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        // db(x, y);
        adj[x].insert(y);
        adj[y].insert(x);
    }
    vector<int> sizes(n + 1);
    vector<int> minSz(n + 1);
    function<void(int, int)> dfs = [&](int node, int par) {
        sizes[node] = 1;
        int maxSz = 0;
        for (auto &x : adj[node])
        {
            if (x != par)
            {
                dfs(x, node);
                sizes[node] += sizes[x];
                maxSz = max(maxSz, sizes[x]);
            }
        }
        if (par != 0)
        {
            int temp = n - sizes[node];
            maxSz = max(maxSz, temp);
        }
        minSz[node] = maxSz;
        // db(node, par, minSz[node]);
    };
    auto get_centroids = [&]() -> vector<int> {
        vector<int> ret;
        fill(all(sizes), 0);
        fill(all(minSz), 0);
        dfs(1, 0);
        int minSize = MOD;
        // vector<int> ret;
        for (size_t i = 1; i <= n; i++)
        {
            // db(i, minSz[i]);
            if (minSz[i] == minSize)
            {
                ret.pb(i);
            }
            else if (minSz[i] < minSize)
            {
                ret = {int(i)};
                minSize = minSz[i];
            }
        }
        return ret;
    };
    auto centroid = get_centroids();
    // for (auto &x : centroid)
    // {
    //     cout << x << ' ';
    // }
    // cout << '\n';
    db(centroid);
    if (centroid.size() == 1)
    {
        int u = *adj[1].begin();
        cout << 1 << ' ' << u << '\n';
        cout << 1 << ' ' << u << '\n';
    }
    else if (centroid.size() == 2)
    {
        if (!adj[centroid[0]].count(centroid[1]))
        {
            db(centroid);
            db(n);
            for (size_t i = 1; i <= n; i++)
                db(i, adj[i]);
            exit(1);
        }

        for (auto &x : adj[centroid[0]])
            adj[x].erase(centroid[0]);
        auto back = adj[centroid[0]];
        adj[centroid[0]].clear();

        UnionFind U(n + 1);
        for (size_t i = 1; i <= n; i++)
            for (auto &x : adj[i])
                U.unionSet(i, x);

        int max1 = 0, max2 = 0;
        for (auto &i : back)
        {
            db(i, U.sizeOfSet(i));
            if (U.sizeOfSet(i) >= max1)
            {
                max2 = max1;
                max1 = i;
            }
            else if (U.sizeOfSet(i) >= max2)
            {
                max2 = i;
            }
        }
        cout << centroid[0] << ' ' << max2 << '\n';
        cout << max1 << ' ' << max2 << '\n';
    }
    else
    {
        db(n);
        db(centroid);
        for (size_t i = 1; i <= n; i++)
            db(i, adj[i]);
        exit(1);
    }
}

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
