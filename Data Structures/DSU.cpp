template<int N>
struct DSU {
	int par[N + 1], sz[N + 1];
	DSU() {
		for (int i = 0; i <= N; i++) {
			par[i] = i, sz[i] = 1;
		}
	}
	int root(int v) {
		return v == par[v] ? v : par[v] = root(par[v]);
	}
	bool unite(int a, int b) {
		a = root(a);
		b = root(b);
		if (a == b) {
			return false;
		}
		if (sz[a] < sz[b]) {
			swap(a, b);
		}
		sz[a] += sz[b];
		par[b] = a;
		return true;
	}
};