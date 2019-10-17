//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
#ifdef WIN32
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

void solve()
{
	int n;
	cin >> n;
	int *a = new int[n];
	int *next = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		next[i] = i + 1;
	}
	next[n - 1] = -1;
	int time = 0;
	int *toKill1 = new int[n];
	int *toKill2 = new int[n];
	int nToKill1 = 0;
	for (int i = 0; next[i] >= 0; ++i)
		if (a[i] > a[next[i]])
			toKill1[nToKill1++] = i;
	while (nToKill1)
	{
		db(nToKill1);
		++time;
		int nToKill2 = 0;
		int pos = 0;
		while (pos < nToKill1)
		{
			int start = toKill1[pos];
			int last = next[start];
			++pos;
			while (pos < nToKill1 && toKill1[pos] == last)
			{
				last = next[last];
				++pos;
			}
			next[start] = next[last];
			if (next[start] >= 0 && a[start] > a[next[start]])
				toKill2[nToKill2++] = start;
		}
		swap(toKill1, toKill2);
		nToKill1 = nToKill2;
	}
	cout << time << '\n';
}

int main()
{
#ifndef WIN32
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}