/*
* Description: Standard BIT for point updates and range queries
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
template<class T, int N>struct BIT
{
    T f[N+1];
    BIT(){memset(f, 0, sizeof f);}
    void upd(int pos, T val)
    {
        for(; pos<=N; pos+=pos&-pos)
            f[pos]+=val;
    }
    T query(int r)
    {
        T ret=0;
        for(; r>0; r-=r&-r)ret+=f[r];
        return ret;
    }
    T query(int l, int r)
    {
        return query(r)-query(l-1);
    }
};
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    BIT<ll, 100000>tree;
    tree.upd(1, 3);
    tree.upd(3, 5);
    cout<<tree.query(1, 3)<<"\n";
    cout<<tree.query(2, 3)<<"\n";
    cout<<tree.query(1, 2)<<"\n";
    return 0;
}
