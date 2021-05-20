struct MinDeque {
	deque<pii> D;
	int lo, hi;
	MinDeque() {
		lo = 1, hi = 1;
	}
	void ins(int val) {
		while (sz(D) && D.back().x >= val) {
			D.pop_back();
		}
		D.pb({val, hi++});
	}
	void del() {
		if (sz(D) && D.front().y == lo++) {
			D.pop_front();
		}
	}
	int get() {
		return sz(D) ? D.front().x : mod;
	}
};