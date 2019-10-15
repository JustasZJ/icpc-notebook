/*
* Description: Finding 2-edge connected components using Tarjan's algorithm and DSU
* Verification: https://codeforces.com/contest/1000/problem/E
*/
#include <bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int>pii;
const int maxn=3e5+100;
int n, m, val[maxn], low[maxn], timer=1, par[maxn], sz[maxn], vis[maxn];
vector<int>adj[maxn], g[maxn];
vector<pii>bridges;
int root(int v)
{
    if(v==par[v])return v;
    else return par[v]=root(par[v]);
}
void unite(int a, int b)
{
    if((a=root(a))==(b=root(b)))return;
    if(sz[a]<sz[b])swap(a, b);
    par[b]=a;
    sz[a]+=sz[b];
}
void tarjan(int v, int p=-1)
{
    val[v]=low[v]=timer++;
    for(auto to:adj[v])
    {
        if(to==p)continue;
        if(!val[to])
        {
            tarjan(to, v);
            low[v]=min(low[v], low[to]);
            if(low[to]>val[v])bridges.pb({v, to});
            else unite(v, to);
        }
        else low[v]=min(low[v], val[to]);
    }
}
void construct()
{
    for(auto p:bridges)
    {
        int a=root(p.x), b=root(p.y);
        g[a].pb(b);
        g[b].pb(a);
    }
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        par[i]=i, sz[i]=1;
    for(int i=0; i<m; i++)
    {
        int a, b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    tarjan(1);
    construct();
    int v=1, d=0;
    for(int i=1; i<=n; i++)if(sz(g[i]))v=i;
    queue<pii>Q;
    Q.push({v, 0});
    vis[v]=1;
    while(!Q.empty())
    {
        v=Q.front().x;
        d=Q.front().y;
        Q.pop();
        for(auto to:g[v])
            if(!vis[to])
            {
                vis[to]=1;
                Q.push({to, d+1});
            }
    }
    Q.push({v, 0});
    for(int i=0; i<maxn; i++)vis[i]=0;
    vis[v]=1;
    while(!Q.empty())
    {
        v=Q.front().x;
        d=Q.front().y;
        Q.pop();
        for(auto to:g[v])
            if(!vis[to])
            {
                vis[to]=1;
                Q.push({to, d+1});
            }
    }
    cout<<d<<"\n";
    return 0;
}
