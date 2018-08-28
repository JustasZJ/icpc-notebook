/*
* Description: Offline Lowest Common Ancestor with NlogN preprocessing and logN query using binary lifting
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
const int maxn=1e5+100;
const int maxlog=20;
int depth[maxn];
int par[maxn][maxlog];
vector<int>adj[maxn];
int n;
void dfs(int v, int p=-1)
{
    par[v][0]=p;
    if(p!=-1)depth[v]=depth[p]+1;
    for(int i=1; i<maxlog; i++)
        if(par[v][i-1]!=-1)
            par[v][i]=par[par[v][i-1]][i-1];
    for(auto to:adj[v])
    {
        if(to==p)continue;
        dfs(to, v);
    }
}
int lca(int v, int u)
{
    if(depth[v]<depth[u])swap(v, u);
    for(int i=maxlog-1; i>=0; i--)
        if(par[v][i]!=-1&&depth[par[v][i]]>=depth[u])
            v=par[v][i];
    if(v==u)return v;
    for(int i=maxlog-1; i>=0; i--)
        if(par[v][i]!=par[u][i])
            v=par[v][i], u=par[u][i];
    return par[v][0];
}
int main()
{
    memset(par, -1, sizeof par);
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin>>n;
    for(int i=0; i<n-1; i++)
    {
        int a, b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(1);
    return 0;
}
