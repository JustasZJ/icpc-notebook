template<class T, int N>
struct BIT {
    T f[N + 1];
    BIT() {
        memset(f, 0, sizeof f);
    }
    void upd(int pos, T val) {
        for (; pos <= N; pos += pos & -pos)
            f[pos] += val;
    }
    T query(int r) {
        T ret = 0;
        for (; r > 0; r -= r & -r) {
            ret += f[r];
        }
        return ret;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
