struct edge {
    int to, flow, cap, cost;
};
vector<edge> edges;
vector<int> adj[maxn];
void add_edge(int a, int b, int cap) {
    adj[a].push_back(edges.size());
    edges.push_back({b, 0, cap});
    adj[b].push_back(edges.size());
    edges.push_back({a, 0, 0});
}
int vis[maxn], pid[maxn], s, t;
int bfs() {
    queue<pair<int, int>> Q;
    vis[s] = 1;
    Q.push({s, mod});
    while (!Q.empty()) {
        int v, flow;
        tie(v, flow) = Q.front();
        Q.pop();
        if (v == t) {
            return flow;
		}
        for (int j : adj[v]) {
            edge e = edges[j];
            if (!vis[e.to] && e.cap - e.flow > 0) {
                vis[e.to] = 1;
                pid[e.to] = j;
                Q.push({e.to, min(e.cap - e.flow, flow)});
            }
        }
    }
    return 0;
}
int max_flow() {
    int maxflow = 0;
    while (true) {
        memset(vis, 0, sizeof vis);
        int cur_flow = bfs();
        if (cur_flow == 0) {
            break;
		}
        maxflow += cur_flow;
        int v = t;
        while (v != s) {
            int j = pid[v];
            edges[j].flow += cur_flow;
            edges[j ^ 1].flow -= cur_flow;
            v = edges[j ^ 1].to;
        }
    }
    return maxflow;
}