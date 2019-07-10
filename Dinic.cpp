struct edge
{
    int to, flow, cap;
};
vector<edge>edges;
vector<int>adj[maxn];
void add_edge(int a, int b, int cap)
{
    edge ab = {b, 0, cap};
    edge ba = {a, 0, 0};
    adj[a].pb(sz(edges));
    edges.pb(ab);
    adj[b].pb(sz(edges));
    edges.pb(ba);
}
int vis[maxn], ptr[maxn], level[maxn], s, t;
bool bfs()
{
    queue<int>Q;
    Q.push(s);
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        for (int id : adj[v])
        {
            edge e = edges[id];
            if (e.cap - e.flow < 1)
                continue;
            if (level[e.to] != -1)
                continue;
            level[e.to] = level[v] + 1;
            Q.push(e.to);
        }
    }
    return level[t] != -1;
}
int dfs(int v, int pushed)
{
    if (pushed == 0)
        return 0;
    if (v == t)
        return pushed;
    for (int& j = ptr[v]; j < sz(adj[v]); j++)
    {
        edge e = edges[adj[v][j]];
        if (level[v] + 1 != level[e.to] || e.cap - e.flow < 1)
            continue;
        int tr = dfs(e.to, min(pushed, e.cap - e.flow));
        if (tr == 0)
            continue;
        edges[adj[v][j]].flow += tr;
        edges[adj[v][j] ^ 1].flow -= tr;
        return tr;
    }
    return 0;
}
int max_flow()
{
    int flow = 0;
    while (true)
    {
        memset(level, -1, sizeof level);
        level[s] = 0;
        if (!bfs())
            break;
        memset(ptr, 0, sizeof ptr);
        while (int pushed = dfs(s, mod))
            flow += pushed;
    }
    return flow;
}