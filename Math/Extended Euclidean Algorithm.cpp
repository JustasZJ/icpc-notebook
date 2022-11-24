const ll mod = 1e9 + 7;
ll gcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	ll x1, y1;
	ll ret = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return ret;
}
ll modinv(ll a) {
	ll x, y;
	gcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}