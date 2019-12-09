template<class T> bool ckmin(T& a, const T& b) { return a > b ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

int hungarian(const vector<vector<int> >& a) { 
	int n = sz(a) - 1, m = sz(a[0]) - 1; // jobs 1..n, workers 1..m
	vector<int> u(n + 1), v(m + 1); // potentials
	vector<int> p(m + 1); // p[j] -> job picked by worker j
	for(int i = 1; i <= n; i++) { // find alternating path with job i
		p[0] = i; int j0 = 0; // add "dummy" worker 0
		vector<int> dist(m + 1,INT_MAX), pre(m + 1,-1); // prev vertex on shortest path
		vector<bool> done(m + 1, false);
		do { // dijkstra
			done[j0] = true; // fix dist[j0], update dists from j0
			int i0 = p[j0], j1; 
			int delta = INT_MAX;
			for(int j = 1; j <= m; j++)
				if (!done[j]) { 
					auto cur = a[i0][j] - u[i0]-v[j]; 
					if (ckmin(dist[j], cur)) 
						pre[j] = j0;
					if (ckmin(delta, dist[j])) 
						j1 = j;
				}
			for(int j = 0; j <= m; j++) { // subtract constant from all edges going 
				// from done -> not done vertices, lowers all 
				// remaining dists by constant
				if (done[j]) 
					u[p[j]] += delta, v[j] -= delta; 
				else 
					dist[j] -= delta; 
			}
			j0 = j1;
		} while (p[j0]); // potentials adjusted so that all edge weights are non-negative
		// perfect matching has zero weight and
		// costs of augmenting paths do not change
		while (j0) { // update jobs picked by workers on alternating path
			int j1 = pre[j0];
			p[j0] = p[j1];
			j0 = j1;
		} 
	}
	return -v[0]; // min cost
}