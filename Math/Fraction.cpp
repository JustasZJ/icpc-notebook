/*
 * Description: Fraction struct
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
struct fraction {
    ll sk, v;
    fraction() {
        sk = 0, v = 1;
    }
    fraction(ll _sk, ll _v) {
        sk = _sk, v = _v;
        ll dbd = __gcd(sk, v);
        sk /= dbd, v /= dbd;
        if (v < 0) sk *= -1, v *= -1;
    }
};
fraction abs(fraction f) { return fraction(abs(f.sk), f.v); }
bool operator<(const fraction &a, const fraction &b) { return a.sk * b.v < b.sk * a.v; }
bool operator>(const fraction &a, const fraction &b) { return a.sk * b.v > b.sk * a.v; }
bool operator==(const fraction &a, const fraction &b) { return a.sk == b.sk && a.v == b.v; }
bool operator!=(const fraction &a, const fraction &b) { return !(a == b); }
fraction operator+(const fraction &a, const fraction &b) { return fraction(a.sk * b.v + b.sk * a.v, a.v * b.v); }
fraction operator+=(fraction &a, const fraction &b) { return a = a + b; }
fraction operator-(const fraction &a, const fraction &b) { return fraction(a.sk * b.v - b.sk * a.v, a.v * b.v); }
fraction operator-=(fraction &a, const fraction &b) { return a = a - b; }
fraction operator*(const fraction &a, const fraction &b) { return fraction(a.sk * b.sk, a.v * b.v); }
fraction operator*=(fraction &a, const fraction &b) { return a = a * b; }
fraction operator*(int a, const fraction &b) { return fraction(a * b.sk, b.v); }
fraction operator*(const fraction &a, int b) { return fraction(a.sk * b, a.v); }
fraction operator/(const fraction &a, const fraction &b) { return fraction(a.sk * b.v, a.v * b.sk); }
fraction operator/=(fraction &a, const fraction &b) { return a = a / b; }
ostream &operator<<(ostream &strm, const fraction &a) {
    if (a.v == 1)
        strm << a.sk;
    else
        strm << a.sk << "/" << a.v;
    return strm;
}
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int q, w, e, r;
    cin >> q >> w >> e >> r;
    fraction a(q, w);
    fraction b(e, r);
    cout << "< " << (a < b) << "\n";
    cout << "> " << (a > b) << "\n";
    cout << "== " << (a == b) << "\n";
    cout << "!= " << (a != b) << "\n";
    cout << "+ " << (a + b) << "\n";
    cout << "- " << (a - b) << "\n";
    cout << "* " << (a * b) << "\n";
    cout << "/ " << (a / b) << "\n";
    return 0;
}
