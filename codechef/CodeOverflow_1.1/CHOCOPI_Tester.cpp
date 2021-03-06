/*
Problem Name: Pick Chocolates
Problem Code: CHOCOPI
Problem Link: https://www.codechef.com/COFW2020/problems/CHOCOPI

Author Name: Mohammed Shahraaz Hussain
Author Link: https://www.codechef.com/users/shahraaz
*/
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
 
struct median
{
    int Sz;
    ll lmed, rmed, suml, sumr;
    priority_queue<int> Left;
    priority_queue<int, vector<int>, greater<int>> Right;
    median()
    {
        Sz = 0;
        lmed = rmed = suml = sumr = 0;
    }
    void insert(int elem)
    {
        if (Sz & 1)
        {
            Right.push(elem);
            sumr += elem;
        }
        else
        {
            Left.push(elem);
            suml += elem;
        }
        Sz++;
        if (Sz > 1)
        {
            db("Start", Left.top(), Right.top());
            while (Left.top() > Right.top())
            {
                db(Left.top(), Right.top());
                auto a = Left.top();
                Left.pop();
                suml -= a;
                auto b = Right.top();
                Right.pop();
                sumr -= b;
                Left.push(b);
                suml += b;
                Right.push(a);
                sumr += a;
            }
            db("End", Left.top(), Right.top());
        }
        if (Sz & 1)
        {
            lmed = rmed = Left.top();
        }
        else
        {
            lmed = Left.top();
            rmed = Right.top();
        }
    }
    ll getAns()
    {
        if (Sz & 1)
        {
            db(lmed, suml, sumr, Left.size(), Right.size());
            return 2 * (lmed * (Left.size() - Right.size()) + sumr - suml);
        }
        else
        {
            db(lmed, rmed, suml, sumr, Left.size(), Right.size());
            return min(2 * (lmed * (Left.size() - Right.size()) + sumr - suml), 2 * (rmed * (Left.size() - Right.size()) + sumr - suml));
        }
    }
};
 
void solveCase()
{
    int q;
    cin >> q;
    median M;
    while (q--)
    {
        int a = 0;
        cin >> a;
        M.insert(a);
        cout << M.getAns() << '\n';
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
 