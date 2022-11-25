#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct point {
    ll x, y;
    point(ll a = 0, ll b = 0) {
        x = a, y = b;
    }
    bool operator<(const point &o) const {
        return make_pair(x, y) < make_pair(o.x, o.y);
    }
    bool operator==(const point& o) const {
        return x == o.x && y == o.y;
    }
    point operator-(const point &b) const {
        return point(x - b.x, y - b.y);
    }
};
ll cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
ll cross(point a, point b, point c) {
    return cross(b - a, c - a);
}
vector<point> convex_hull(vector<point>pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<point>top, bot;
    for (int i = 0; i < pts.size(); ++i) {
        while (bot.size() >= 2 && cross(bot[bot.size() - 2], bot.back(), pts[i]) <= 0) {
            bot.pop_back();
        }
        bot.push_back(pts[i]);
    }
    bot.pop_back();
    for (int i = pts.size() - 1; i >= 0; --i) {
        while (top.size() >= 2 && cross(top[top.size() - 2], top.back(), pts[i]) <= 0) {
            top.pop_back();
        }
        top.push_back(pts[i]);
    }
    top.pop_back();
    top.insert(top.end(), bot.begin(), bot.end());
    return top;
}
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n;
    cin >> n;
    vector<point>pts;
    for (int i = 0; i < n; i++) {
        point p;
        cin >> p.x >> p.y;
        pts.push_back(p);
    }
    vector<point>hull = convex_hull(pts);
    cout << "------\n";
    for (point p : hull) {
        cout << p.x << " " << p.y << "\n";
    }
    return 0;
}
