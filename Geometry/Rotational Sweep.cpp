#include <bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define x first
#define y second
#define debug(...) "["<<#__VA_ARGS__<<": "<<__VA_ARGS__<<"]"
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int>pii;
const int maxn = 1e6 + 100;
const int mod = 1e9 + 7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
struct point
{
    ll x, y;
    point() {}
    point(ll a, ll b)
    {
        x=a;
        y=b;
    }
    point operator+(const point &o)
    {
        return point(x+o.x, y+o.y);
    }
    point operator-(const point &o)
    {
        return point(x-o.x, y-o.y);
    }
};
ll cross(point a, point b)
{
    return a.x*b.y-a.y*b.x;
}
int n;
ll ans;
vector<point>v;
void sweep(int id) {
    vector<point>u;
    for(int i = 0; i < n; i++) {
        if(i != id) {
            u.push_back(v[i]);
        }
    }
    point p = v[id];
    sort(u.begin(), u.end(), [&](point a, point b) {
        if((a.y >= p.y) != (b.y >= p.y)) {
            return a.y >= p.y;
        }
        return cross(a - p, b - p) < 0;
    });
    int r = 0, cnt = 0;
    for(int l = 0; l < u.size(); l++) {
        if (l > 0) {
            cnt--;
        }
        int rr = (r + 1) % u.size();
        while (cnt != n - 2 && cross(u[l] - p, u[rr] - p) <= 0) {
            cnt++;
            rr = (rr + 1) % u.size();
        }
        r = rr - 1;
        ll R = (r - l + u.size()) % u.size(), L = n - R - 2;
        ans += R * (R - 1) / 2 * L * (L - 1) / 2;
    }
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; i++)
        cin >> v[i].x >> v[i].y;
    for(int i = 0; i < n; i++)
        sweep(i);
    cout << ans / 2 << "\n";
    return 0;
}