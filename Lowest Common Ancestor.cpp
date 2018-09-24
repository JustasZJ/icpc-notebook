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
int dep[maxn], anc[maxn][maxlog];
vector<int>adj[maxn];
void dfs(int v)
{
    for(int i=1; i<maxlog; i++)
        anc[v][i]=anc[anc[v][i-1]][i-1];
    for(auto to:adj[v])
    {
        if(to==anc[v][0])continue;
        anc[to][0]=v;
        dep[to]=dep[v]+1;
        dfs(to);
    }
}
int lca(int v, int u)
{
    if(dep[v]<dep[u])swap(v, u);
    for(int i=maxlog-1; i>=0; i--)
        if(anc[v][i] && dep[anc[v][i]]>=dep[u])
            v=anc[v][i];
    if(v==u)return v;
    for(int i=maxlog-1; i>=0; i--)
        if(anc[v][i]!=anc[u][i])
            v=anc[v][i], u=anc[u][i];
    return anc[v][0];
}
int getDist(int v, int u)
{
    return dep[v]+dep[u]-2*dep[lca(v, u)];
}
