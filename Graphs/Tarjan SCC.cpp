int val[maxn], low[maxn], scc[maxn], siz[maxn], tim, onStack[maxn], cnt;
stack<int> st;
void tarjan(int v) {
	low[v] = val[v] = tim++;
	onStack[v] = 1;
	st.push(v);
	for (int to : adj[v]) {
		if (val[to] == 0) {
			tarjan(to);
			low[v] = min(low[v], low[to]);
		} else if (onStack[to]) {
			low[v] = min(low[v], val[to]);
		}
	}
	if (low[v] == val[v]) {
		cnt++;
		while (true) {
			int u = st.top();
			st.pop();
			onStack[u] = 0;
			scc[u] = cnt;
			++siz[cnt];
			if (u == v) {
				break;
			}
		}
	}
}