struct line {
    ll k, b;
    line() = default;
    line(ll kk, ll bb) {
        k = kk;
        b = bb;
    }
    ll eval(ll x) {
        return k * x + b;
    }
};
ld inter(line f, line s) {
    return 1.0 * (s.b - f.b) / (f.k - s.k);
}
int siz, it;
line hull[maxn];
void add(line a) {
    while (siz >= 2 && inter(hull[siz - 1], hull[siz - 2]) >= inter(hull[siz - 2], a)) {
        siz--;
    }
    hull[siz++] = a;
}

// general approach is binary search
ll get(ll x) {
    // change to < for maximum
    while (it + 1 < siz && hull[it].eval(x) > hull[it + 1].eval(x)) {
        it++;
    }
    return hull[it].eval(x);
}
