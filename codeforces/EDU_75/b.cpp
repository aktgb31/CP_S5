//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

void solve(int caseNo)
{
	int n;
	cin >> n;
	string s;
	vector<int> len, even, odd;
	int zero, one, tot = 0;
	zero = one = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> s;
		int LL = s.length();
		tot += LL;
		for (auto c : s)
			if (c == '0')
				zero++;
			else
				one++;
		if (LL & 1)
			odd.pb(LL);
		else
			even.pb(LL);
	}
	// sort(len.begin(), len.begin() + n);
	// db(one, zero);
	// pc(len);
	// int res = 0;
	db(one, zero);
	pc(odd, even);
	std::sort(odd.begin(), odd.end());
	std::sort(even.begin(), even.end());
	int res = 0;
	for (auto ee : even)
	{
		int kk = min(ee, one / 2 * 2);
		if (zero < (ee - kk))
		{
			cout << n - 1 << '\n';
			return;
		}
		else
		{
			res++;
			one -= kk;
			zero -= ee - kk;
		}
	}
	db(one,zero);
	for (auto oo : odd)
	{
		int kk;
		one--;
		kk = min(oo, one / 2 * 2);
		if (zero < (oo - kk))
		{
			// cout << n - 1 << '\n';
			// return;
		}
		else
		{
			res++;
			one -= kk;
			zero -= oo - kk;
			continue;
		}
		one++;
		zero--;
		kk = min(oo, one / 2 * 2);
		if (zero < (oo - kk))
		{
			// cout << n - 1 << '\n';
			// return;
		}
		else
		{
			res++;
			one -= kk;
			zero -= oo - kk;
			continue;
		}
	}
	cout << n << '\n';
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