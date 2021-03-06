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

const int nax = 1e6 + 10, mod = 1000000007, LOG = 20;
int cnt[1 << LOG], powe[1 << LOG];

void solve(int caseNo)
{
	int n, x;
	cin >> n;
	// db(LOG, 1 << LOG);
	powe[0] = 1;
	for (int i = 0; i < n; i++)
	{
		powe[i + 1] = (powe[i] * 2LL) % mod;
		cin >> x;
		cnt[((1 << LOG) - 1) ^ x]++;
	}
	for (int i = 0; i < 20; ++i)
		for (int mask = 0; mask < (1 << LOG); ++mask)
			if (!(mask & (1 << i)))
				cnt[mask | (1 << i)] += cnt[mask];
	ll ret = 0;
	for (int mask = 0; mask < (1 << LOG); ++mask)
	{
		int Cnt = 0;
		for (int i = 0; i < 20; ++i)
			if (mask & (1 << i))
				Cnt++;
		if (Cnt & 1)
			ret = (ret + mod - powe[cnt[mask]]) % mod;
		else
			ret = (ret + powe[cnt[mask]]) % mod;
	}
	cout << ret << '\n';
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
	for (int i = 0; i < t; ++i)
		solve(i);
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}