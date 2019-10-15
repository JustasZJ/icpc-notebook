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
const ll mod=1e9+7;
ll pwr(ll num, ll pw)
{
    ll ret=1;
    while(pw>0)
    {
        if(pw&1)ret=(ret*num)%mod;
        num=(num*num)%mod;
        pw>>=1;
    }
    return ret;
}
ll modinv(ll a){ return pwr(a, mod-2); }
ll add(ll a, ll b){ return (a+b)%mod; }
ll sub(ll a, ll b){ return (a-b+mod)%mod; }
ll mul(ll a, ll b){ return (a*b)%mod; }

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    return 0;
}
