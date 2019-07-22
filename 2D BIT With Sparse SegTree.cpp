int root[maxn], seg[maxn * 100], L[maxn * 100], R[maxn * 100], nxt_id;
int modify(int id, int pos, int val, int l = 1, int r = n)
{
	if(!id)
		id = ++nxt_id;
	if(l == r)
	{
		seg[id] = val;
		return id;
	}
	int mid = (l + r) / 2;
	if(pos <= mid)
		L[id] = modify(L[id], pos, val, l, mid);
	else
		R[id] = modify(R[id], pos, val, mid + 1, r);
	seg[id] = seg[L[id]] + seg[R[id]];
	return id;
}
int query(int id, int x, int y, int l = 1, int r = n)
{
	if(l > y || r < x || !id)
		return 0;
	if(l >= x && r <= y)
		return seg[id];
	int mid = (l + r) / 2;
	return query(L[id], x, y, l, mid) + query(R[id], x, y, mid + 1, r);
}
void add(int x, int y)
{
	for(; x <= n; x += x & -x)
		root[x] = modify(root[x], y, 1);
}
int get(int x, int lo, int hi)
{
	int ret = 0;
	for(; x > 0; x -= x & -x)
		ret += query(root[x], lo, hi);
	return ret;
}
int get(int l, int r, int lo, int hi)
{
	return get(r, lo, hi) - get(l - 1, lo, hi);
}