/* Description: Offline Lowest Common Ancestor with NlogN preprocessing and logN query using binary lifting */
const int maxn = 1e5 + 100;
const int maxlog = 20;
int dep[maxn], anc[maxn][maxlog];
vector<int> adj[maxn];
void dfs(int v, int p = 0) {
    dep[v] = dep[p] + 1;
    anc[v][0] = p;
    for (int i = 1; i < 18; i++) {
        anc[v][i] = anc[anc[v][i - 1]][i - 1];
    }
    for (int to : adj[v]) {
        if (to != p) {
            dfs(to, v);
        }
    }
}
int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int i = 17; i >= 0; i--) {
        if (dep[anc[a][i]] >= dep[b]) {
            a = anc[a][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = 17; i >= 0; i--) {
        if (anc[a][i] != anc[b][i]) {
            a = anc[a][i], b = anc[b][i];
        }
    }
    return anc[a][0];
}
int getDist(int v, int u) {
    return dep[v] + dep[u] - 2 * dep[lca(v, u)];
}
