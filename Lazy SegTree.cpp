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
template<int N>struct SegTree
{
    ll seg[N*4], lazy[N*4];
    SegTree()
    {
        memset(seg, 0, sizeof seg);
        memset(lazy, 0, sizeof lazy);
    }
    void build(ll arr[], int id=1, int l=0, int r=N)
    {
        if(r-l<2)
        {
            seg[id]=arr[l];
            return;
        }
        int mid=(l+r)/2;
        build(arr, id*2, l, mid);
        build(arr, id*2+1, mid, r);
        seg[id]=seg[id*2]+seg[id*2+1];
    }
    void upd(int id, int l, int r, ll val)
    {
        seg[id]+=(ll)(r-l)*val;
        lazy[id]+=val;
    }
    void shift(int id, int l, int r)
    {
        int mid=(l+r)/2;
        upd(id*2, l, mid, lazy[id]);
        upd(id*2+1, mid, r, lazy[id]);
        lazy[id]=0;
    }
    void modify(int x, int y, ll val, int id=1, int l=0, int r=N)
    {
        if(l>=y || r<=x)return;
        if(l>=x && r<=y)
        {
            upd(id, l, r, val);
            return;
        }
        shift(id, l, r);
        int mid=(l+r)/2;
        modify(x, y, val, id*2, l, mid);
        modify(x, y, val, id*2+1, mid, r);
        seg[id]=seg[id*2]+seg[id*2+1];
    }
    ll query(int x, int y, int id=1, int l=0, int r=N)
    {
        if(l>=y || r<=x)return 0;
        if(l>=x && r<=y)return seg[id];
        shift(id, l, r);
        int mid=(l+r)/2;
        return query(x, y, id*2, l, mid)+query(x, y, id*2+1, mid, r);
    }
};
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    return 0;
}
