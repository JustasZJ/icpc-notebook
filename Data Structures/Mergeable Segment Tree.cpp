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
const int maxn = 2e5 + 100;
const int mod = 1e9 + 7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct node {
    int l, r;
};
int n, q, ans[maxn], nxt_id;
node tree[maxn * 150];
int root[105];
pii split(int id, int k, int lo = 1, int hi = n) { /// >= goes to the right
    if (!id) {
        return {0, 0};
    }
    if (lo == hi) {
        return (lo >= k ? pii(0, id) : pii(id, 0));
    }
    int other = ++nxt_id;
    int mid = (lo + hi) / 2;
    if (k <= mid) {
        pii p = split(tree[id].l, k, lo, mid);
        tree[id].l = p.y;
        tree[other].l = p.x;
        return {other, id};
    } else {
        pii p = split(tree[id].r, k, mid + 1, hi);
        tree[id].r = p.x;
        tree[other].r = p.y;
        return {id, other};
    }
}
int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    tree[a].l = merge(tree[a].l, tree[b].l);
    tree[a].r = merge(tree[a].r, tree[b].r);
    return a;
}
int ins(int id, int pos, int lo = 1, int hi = n) {
    if (!id) id = ++nxt_id;
    if (lo == hi) return id;
    int mid = (lo + hi) / 2;
    if (pos <= mid) {
        tree[id].l = ins(tree[id].l, pos, lo, mid);
    } else {
        tree[id].r = ins(tree[id].r, pos, mid + 1, hi);
    }
    return id;
}
void go(int id, int x, int lo = 1, int hi = n) {
    if (!id) {
        return;
    }
    if (lo == hi) {
        ans[lo] = x;
        return;
    }
    int mid = (lo + hi) / 2;
    go(tree[id].l, x, lo, mid);
    go(tree[id].r, x, mid + 1, hi);
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        root[x] = ins(root[x], i);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        if (x == y) {
            continue; /// DOESNT WORK IF X = Y
        }
        pii a = split(root[x], l);
        pii b = split(a.y, r + 1);
        root[y] = merge(root[y], b.x);
        root[x] = merge(a.x, b.y);
    }
    for(int i = 1; i <= 100; i++) {
        go(root[i], i);
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;
}
