int root[maxn], seg[maxn * 60], L[maxn * 60], R[maxn * 60], next_id; /// required size can be different depending on problem
void build(int id = 1, int l = 1, int r = n)
{
    if(l == r) return;
    int mid = (l + r) / 2;
    L[id] = ++next_id;
    R[id] = ++next_id;
    build(L[id], l, mid);
    build(R[id], mid + 1, r);
}
int modify(int pos, int delta, int id, int l = 1, int r = n)
{
    int new_id = ++next_id;
    seg[new_id] = seg[id] + delta;
    if(l == r)
        return new_id;
    int mid = (l + r) / 2;
    L[new_id] = L[id], R[new_id] = R[id];
    if(pos <= mid)
        L[new_id] = modify(pos, delta, L[new_id], l, mid);
    else
        R[new_id] = modify(pos, delta, R[new_id], mid + 1, r);
    return new_id;
}