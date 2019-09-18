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
	std::cerr << name << " { ";
	for (const auto &v : arg)
		cerr << v << ' ';
	cerr << " }\n";
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
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10;

void solve()
{
	int a1, a2, k1, k2, n;
	cin >> a1 >> a2 >> k1 >> k2 >> n;
	int n1 = n;
	int ans = 0;
	{
		int temp = (n) / k1;
		temp = min(temp, a1);
		ans += temp;
		n -= temp * k1;
		temp = n / k2;
		temp = min(temp, n);
		ans += temp;
	}
	n = n1;
	int ans1 = ans;
	ans = 0;
	{
		swap(a1, a2);
		swap(k1, k2);
		int temp = (n) / k1;
		temp = min(temp, a1);
		ans += temp;
		n -= temp * k1;
		temp = n / k2;
		temp = min(temp, n);
		ans += temp;
	}
	n = n1;
	ans = max(ans, ans1);
	int cnt = (k1 - 1) * a1 + (k2 - 1) * a2;
	db(cnt);
	n = max(0, n - cnt);
	cout << n << ' ';
	cout << ans << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
	flush(cout);
	cin >> t;
#endif
	return 0;
}