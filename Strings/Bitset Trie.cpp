template <int N>
struct trie {
    int t[N + 1][2], nxt = 1;

    trie() {
        memset(t, 0, sizeof t);
    }

    void ins(string s) {
        int cur = 0;
        for (int i = 0; i < s.size(); ++i) {
            int bit = s[i] - '0';
            if (!t[cur][bit]) {
				t[cur][bit] = nxt++;
			}
            cur = t[cur][bit];
        }
    }

    bool fnd(string s) {
        int cur = 0;
        for (int i = 0; i < s.size(); ++i) {
            int bit = s[i] - '0';
            if (!t[cur][bit]) {
				return false;
			}
            cur = t[cur][bit];
        }
        return true;
    }
};