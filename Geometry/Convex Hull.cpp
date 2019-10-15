/*
* Source: https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
* Description: NlogN Convex Hull
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
typedef pair<ll, ll>pii;
const int maxn=1e5+100;

ll cross(pii a, pii b, pii c)///(B-A)x(C-A)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
vector<pii> convex_hull(vector<pii>pts)
{
    sort(all(pts));
    pts.erase(unique(all(pts)), pts.end());
    vector<pii>top, bot;
    for(int i=0; i<sz(pts); ++i)
    {
        while(sz(bot)>=2 && cross(bot[sz(bot)-2], bot.back(), pts[i])<=0)
            bot.pop_back();
        bot.pb(pts[i]);
    }
    bot.pop_back();
    for(int i=sz(pts)-1; i>=0; --i)
    {
        while(sz(top)>=2 && cross(top[sz(top)-2], top.back(), pts[i])<=0)
            top.pop_back();
        top.pb(pts[i]);
    }
    top.pop_back();
    top.insert(top.end(), all(bot));
    return top;
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n;
    cin>>n;
    vector<pii>pts;
    for(int i=0; i<n; i++)
    {
        ll a, b;
        cin>>a>>b;
        pts.pb({a, b});
    }
    vector<pii>hull=convex_hull(pts);
    cout<<"------\n";
    for(auto aa:hull)
        cout<<aa.x<<" "<<aa.y<<"\n";
    return 0;
}
