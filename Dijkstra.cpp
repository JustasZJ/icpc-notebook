ll D[maxn];
vector<pii>adj[maxn];
void Dijkstra(int st)
{
    fill(D, D+maxn, LLONG_MAX);
    priority_queue<pii, vector<pii>, greater<pii> >Q;
    Q.push({D[st]=0, st});
    while(sz(Q))
    {
        pii v=Q.top();Q.pop();
        if(D[v.y]<v.x)continue;
        for(auto to:adj[v.y])if(v.x+to.y<D[to.x])
            Q.push({D[to.x]=v.x+to.y, to.x});
    }
}