/*
 * Description: Finding 2-edge connected components using Tarjan's algorithm and DSU
 * Verification: https://codeforces.com/contest/1000/problem/E
 */
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
typedef long double ld;
const int maxn = 3e5 + 100;
int n, m, val[maxn], low[maxn], timer = 1, par[maxn], sz[maxn], vis[maxn];
vector<int> adj[maxn], g[maxn];
vector<pair<int, int>> bridges;
int root(int v) {
	return v == par[v] ? v : par[v] = root(par[v]);
}
void unite(int a, int b) {
	a = root(a), b = root(b);
	if (a == b) {
		return;
	}
	if (sz[a] < sz[b]) {
		swap(a, b);
	}
	par[b] = a;
	sz[a] += sz[b];
}
void tarjan(int v, int p = -1) {
	val[v] = low[v] = timer++;
	for (auto to : adj[v]) {
		if (to == p) {
			continue;
		}
		if (!val[to]) {
			tarjan(to, v);
			low[v] = min(low[v], low[to]);
			if (low[to] > val[v]) {
				bridges.push_back({v, to});
			} else {
				unite(v, to);
			}
		} else {
			low[v] = min(low[v], val[to]);
		}
	}
}
void construct() {
	for (pair<int, int> p : bridges) {
		int a = root(p.first), b = root(p.second);
		g[a].push_back(b);
		g[b].push_back(a);
	}
}
int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		par[i] = i, sz[i] = 1;
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	tarjan(1);
	construct();
	int v = 1, d = 0;
	for (int i = 1; i <= n; i++) {
		if (!g[i].empty()) {
			v = i;
		}
	}
	queue<pair<int, int>> Q;
	Q.push({v, 0});
	vis[v] = 1;
	while (!Q.empty()) {
		v = Q.front().first;
		d = Q.front().second;
		Q.pop();
		for (auto to : g[v]) {
			if (!vis[to]) {
				vis[to] = 1;
				Q.push({to, d + 1});
			}
		}
	}
	Q.push({v, 0});
	for (int i = 0; i < maxn; i++) {
		vis[i] = 0;
	}
	vis[v] = 1;
	while (!Q.empty()) {
		v = Q.front().first;
		d = Q.front().second;
		Q.pop();
		for (auto to : g[v]) {
			if (!vis[to]) {
				vis[to] = 1;
				Q.push({to, d + 1});
			}
		}
	}
	cout << d << "\n";
	return 0;
}
