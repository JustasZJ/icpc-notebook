/*
* Description: BIT with range updates and point queries
*/
#include <bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int>pii;
const int maxn = 1e5 + 100;

template<class T, int N>
struct BIT {
	T f[N + 1];
	BIT() {
		memset(f, 0, sizeof f);
	}
	void upd(int pos, T val) {
		for (; pos <= N; pos += pos & -pos)
			f[pos] += val;
	}
	void upd(int l, int r, T val) {
		upd(l, val);
		upd(r + 1, -val);
	}
	T query(int pos) {
		T ret = 0;
		for (; pos > 0; pos -= pos & -pos) {
			ret += f[pos];
		}
		return ret;
	}
};

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);
	BIT<ll, 100000> tree;
	tree.upd(3, 5, 1);
	cout << tree.query(3) << "\n";
	cout << tree.query(4) << "\n";
	cout << tree.query(5) << "\n";
	cout << tree.query(2) << "\n";
	cout << tree.query(6) << "\n";
	return 0;
}
