/*
 * Source: KACTL
 * Description: Linear time string matching
 */
#include <bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int maxn = 1e5 + 100;
vector<int> build_lps(string s) {
    vector<int> lps(sz(s), 0);
    for (int i = 1; i < sz(s); ++i) {
        int id = lps[i - 1];
        while (id && s[i] != s[id]) {
			id = lps[id - 1];
		}
        lps[i] = id + (s[i] == s[id]);
    }
    return lps;
}
vector<int> KMP(string s, string pat) {
    vector<int> lps = build_lps(pat + '\0' + s), res;
    for (int i = 0; i < sz(lps); ++i) {
        if (lps[i] == sz(pat)) {
			res.pb(i - 2 * sz(pat));
		}
	}
    return res;
}
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    string s, pat;
    cin >> s >> pat;
    vector<int> res = KMP(s, pat);
    for (auto aa : res) {
        cout << aa << " ";
	}
    cout << "\n";
    return 0;
}
