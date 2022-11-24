struct edge {
    int to, flow, cap, cost;
    edge(int a = 0, int b = 0, int c = 0, int d = 0) {
        to = a, flow = b, cap = c, cost = d;
    }
};
vector<edge> edges;
vector<int> adj[maxn];
void add_edge(int a, int b, int cap, int cost) {
    edge ab(b, 0, cap, cost);
    edge ba(a, 0, 0, -cost);
    adj[a].push_back(edges.size());
    edges.push_back(ab);
    adj[b].push_back(edges.size());
    edges.push_back(ba);
}
int vis[maxn], pid[maxn], s, t;
int dist[maxn];
pii dijkstra() {
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> Q;
    vis[s] = 1;
    Q.push({0, {s, mod}});
    while (!Q.empty()) {
        int v, flow, w;
        pair<int, pii> p = Q.top();
        Q.pop();
        w = p.x;
        v = p.y.x;
        flow = p.y.y;
        if (dist[v] < w) {
            continue;
		}
        if (v == t) {
            return make_pair(w, flow);
		}
        for (int j : adj[v]) {
            edge e = edges[j];
            if (!vis[e.to] && e.cap - e.flow > 0) {
                if (w + e.cost < dist[e.to]) {
                    dist[e.to] = w + e.cost;
                    pid[e.to] = j;
                    Q.push({dist[e.to], {e.to, min(e.cap - e.flow, flow)}});
                }
            }
        }
    }
    return make_pair(0, 0);
}
pii max_flow() {
    int maxflow = 0, mincost = 0;
    while (true) {
        fill(dist, dist + maxn, mod);
        pii cur_flow = dijkstra();
        if (cur_flow.y == 0) {
            break;
		}
        maxflow += cur_flow.y;
        mincost += cur_flow.x;
        int v = t;
        while (v != s) {
            int j = pid[v];
            edges[j].flow += cur_flow.y;
            edges[j ^ 1].flow -= cur_flow.y;
            v = edges[j ^ 1].to;
        }
    }
    return make_pair(mincost, maxflow);
}