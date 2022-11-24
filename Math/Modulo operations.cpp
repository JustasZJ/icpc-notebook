typedef long long ll;
const ll mod = 1e9 + 7;
ll pwr(ll num, ll pw) {
	ll ret = 1;
	while (pw > 0) {
		if (pw & 1) {
			ret = (ret * num) % mod;
		}
		num = (num * num) % mod;
		pw >>= 1;
	}
	return ret;
}
ll modinv(ll a) { return pwr(a, mod - 2); }
ll add(ll a, ll b) { return (a + b) % mod; }
ll sub(ll a, ll b) { return (a - b + mod) % mod; }
ll mul(ll a, ll b) { return (a * b) % mod; }