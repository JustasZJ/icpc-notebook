/*
* Description: Centroid Decomposition on trees
* Verification: http://codeforces.com/contest/321/problem/C
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
vector<int>adj[maxn];
int n, sub[maxn], par[maxn];
bool vis[maxn];
char ans[maxn];
void dfs(int v)
{
    sub[v]=1;
    for(auto to:adj[v])
        if(!vis[to]&&to!=par[v])
        {
            par[to]=v;
            dfs(to);
            sub[v]+=sub[to];
        }
}
int get_centroid(int v)
{
    par[v]=0;
    dfs(v);
    int sz=sub[v];
    while(true)
    {
        pii mx= {0, 0};
        for(auto to:adj[v])
            if(!vis[to]&&par[v]!=to)
                mx=max(mx, {sub[to], to});
        if(mx.first*2>sz)v=mx.second;
        else return v;
    }
}
void solve(int v, int level=0)
{
    v=get_centroid(v);
    vis[v]=true;
    ans[v]=(char)(level+'A');
    for(auto to:adj[v])
        if(!vis[to])
            solve(to, level+1);
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin>>n;
    for(int i=0; i<n-1; i++)
    {
        int a, b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    solve(1);
    for(int i=1; i<=n; i++)
        cout<<ans[i]<<" ";
    cout<<"\n";
    return 0;
}
