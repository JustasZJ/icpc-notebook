int n;
bool vis[maxn];
int match[maxn];
vector<int>adj[maxn];
bool dfs(int v) {
	if (vis[v]) {
		return false;
	}
	vis[v] = true;
	for (int to : adj[v]) {
		if (match[to] == -1 || dfs(match[to])) {
			match[v] = to, match[to] = v;
			return true;
		}
	}
	return false;
}
void matching() {
	memset(match, -1, sizeof match);
	while (true) {
		memset(vis, 0, sizeof vis);
		bool found = false;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && match[i] == -1) {
				found |= dfs(i);
			}
		}
		if (!found) {
			break;
		}
	}
}