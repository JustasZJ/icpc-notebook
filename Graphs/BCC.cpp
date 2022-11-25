template<class T> bool ckmin(T& a, const T& b) { return a > b ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
struct BCC {
	vector<vector<pair<int, int>>> adj; vector<pair<int, int>> ed; 
	vector<vector<int>> edgeSets, vertSets; // edges for each bcc
	int N, ti = 0; vector<int> disc, stk; 
	void init(int _N) { N = _N; disc.resize(N), adj.resize(N); }
	void ae(int x, int y) { 
		adj[x].emplace_back(y,ed.size()), adj[y].emplace_back(x,ed.size()), ed.emplace_back(x,y); }
	int dfs(int x, int p = -1) { // return lowest disc
		int low = disc[x] = ++ti;
		for (auto &e : adj[x]) if (e.second != p) {
			if (!disc[e.first]) {
				stk.push_back(e.second); // disc[x] < LOW -> bridge
				int LOW = dfs(e.first,e.second); ckmin(low,LOW); 
				if (disc[x] <= LOW) { // get edges in bcc
					edgeSets.emplace_back(); vector<int>& tmp = edgeSets.back(); // new bcc
					for (int y = -1; y != e.second; )
						tmp.push_back(y = stk.back()), stk.pop_back();
				}
			} else if (disc[e.first] < disc[x]) // back-edge
				ckmin(low,disc[e.first]), stk.push_back(e.second);
		}
		return low;
	}
	void gen() { 
		for (int i=0; i<N; i++) if (!disc[i]) dfs(i);  
		vector<bool> in(N);
		for(auto &c : edgeSets) { // edges contained within each BCC
			vertSets.emplace_back(); // so you can easily create block cut tree
			auto ad = [&](int x) { 
				if (!in[x]) in[x] = 1, vertSets.back().push_back(x); };
			for(auto &e : c) ad(ed[e].first), ad(ed[e].second);
			for(auto &e : c) in[ed[e].first] = in[ed[e].second] = 0;
		}
	}
};