int n, m, even;
set<int> adj[maxn];
vector<int> tour;
void dfs(int v) {
    for (auto it = adj[v].begin(); adj[v].size() > 0;) {
        int to = *it;
        it = adj[v].erase(it);
        adj[to].erase(v);
        dfs(to);
    }
    tour.push_back(v);
}
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() % 2 == 0) {
            ++even;
		}
    }
    if (even != n && even != n - 2) {
        /// no tour exists
        return 0;
    }
    int start = 1;
    if (even == n - 2) {
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() % 2 == 1) {
                start = i;
                break;
            }
        }
    }
    dfs(start);
    for (int v : tour) {
        cout << v << " ";
	}
    cout << "\n";
    return 0;
}
