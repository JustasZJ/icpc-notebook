/*
 * Description: Big Integer struct
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
typedef pair<int, int> pii;
const int maxn = 1e5 + 100;
const ll base = 1e18;
const int SZ = 300;
struct BigInt {
	vector<ll> digs;
	bool neg;
	BigInt() {
		digs.assign(SZ, 0);
		neg = false;
	}
	BigInt(ll num) {
		digs.assign(SZ, 0);
		neg = (num < 0);
		digs[0] = abs(num);
	}
	BigInt &operator=(const ll &b) {
		return *this = BigInt(b);
	}
	BigInt &operator=(const BigInt &b) {
		for (int i = 0; i < SZ; i++) {
			digs[i] = b.digs[i];
		}
		neg = b.neg;
		return *this;
	}
};
bool operator<(const BigInt &a, const BigInt &b) {
	if (a.neg != b.neg) return a.neg;
	for (int i = SZ - 1; i >= 0; i--) {
		if (a.digs[i] != b.digs[i]) {
			return (a.digs[i] < b.digs[i]) ^ (a.neg);
		}
	}
	return false;
}
bool operator==(const BigInt &a, const BigInt &b) {
	return !(a < b) && !(b < a);
}
bool operator>(const BigInt &a, const BigInt &b) {
	return b < a;
}
ostream &operator<<(ostream &out, const BigInt &a) {
	if (a.neg) out << "-";
	bool flag = false;
	for (int i = SZ - 1; i >= 0; i--)
		if (a.digs[i] > 0 || flag) {
			if (flag) {
				out << setw(18) << setfill('0') << a.digs[i];
			} else {
				out << a.digs[i];
			}
			flag = true;
		}
	return out;
}
BigInt operator+(const BigInt &a, const BigInt &b) {
	if (a.neg != b.neg) {
		BigInt aa = a, bb = b;
		if (aa.neg) swap(aa, bb);
		BigInt c;
		bb.neg = false;
		c.neg = (aa < bb);
		if (aa < bb) swap(aa, bb);
		ll borrow = 0;
		for (int i = 0; i < SZ; i++) {
			c.digs[i] = aa.digs[i] - bb.digs[i] - borrow;
			if (c.digs[i] < 0) {
				c.digs[i] += base, borrow = 1;
			} else {
				borrow = 0;
			}
		}
		return c;
	} else {
		ll carry = 0;
		BigInt c;
		for (int i = 0; i < SZ; i++) {
			c.digs[i] = a.digs[i] + b.digs[i] + carry;
			if (c.digs[i] >= base) {
				c.digs[i] -= base, carry = 1;
			} else {
				carry = 0;
			}
		}
		c.neg = a.neg;
		return c;
	}
}
BigInt operator+=(BigInt &a, const BigInt &b) {
	return a = a + b;
}
BigInt operator-(BigInt &a, BigInt &b) {
	b.neg ^= true;
	BigInt c = a + b;
	b.neg ^= true;
	return c;
}
BigInt operator-=(BigInt &a, BigInt &b) {
	return a = a - b;
}
BigInt max(BigInt a, BigInt b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}
BigInt min(BigInt a, BigInt b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}
int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	BigInt a, b;
	ll aa, bb;
	cin >> aa >> bb;
	a = BigInt(aa), b = BigInt(bb);
	cout << "a+b " << a + b << "\n";
	cout << "a-b " << a - b << "\n";
	BigInt c = a;
	c += b;
	cout << "a+=b " << c << "\n";
	c = b;
	c += a;
	cout << "b+=a " << c << "\n";
	cout << "a<b " << (a < b) << "\n";
	cout << "a>b " << (a > b) << "\n";
	cout << "a==b " << (a == b) << "\n";
	cout << "max(a, b) " << max(a, b) << "\n";
	cout << "min(a, b) " << min(a, b) << "\n";
	return 0;
}
