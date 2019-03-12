#include <bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define x first
#define y second
#define debug(...) cout << "[" << #__VA_ARGS__ << ": " << __VA_ARGS__ << "]\n"
#define rd() abs((int)rng())
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int>pii;
const int maxn = 1e5 + 100;
const int mod = 1e9 + 7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int n, m, even;
set<int>adj[maxn];
vector<int>tour;
void dfs(int v)
{
	for(auto it = adj[v].begin(); sz(adj[v]) > 0;)
	{
	    int to = *it;
	    it = adj[v].erase(it);
	    adj[to].erase(v);
	    dfs(to);
	}
	tour.pb(v);
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
    	int a, b;
    	cin >> a >> b;
    	adj[a].insert(b);
    	adj[b].insert(a);
    }
    for(int i = 1; i <= n; i++)
    {
    	if(sz(adj[i]) % 2 == 0)
    		++even;
    }
    if(even != n && even != n - 2)
    {
        /// no tour exists
    	return 0;
    }
    int start = 1;
    if(even == n - 2)
    {
    	for(int i = 1; i <= n; i++)
    	{
    		if(sz(adj[i]) % 2 == 1)
    		{
    			start = i;
    			break;
    		}
    	}
    }
    dfs(start);
    for(int v : tour)
    	cout << v << " ";
    cout << "\n";
    return 0;
}
