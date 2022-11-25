// Number of correct bracket sequence consisting of n opening and n closing brackets.
// Number of rooted full binary trees with n + 1 leaves (vertices are not numbered). 
// A rooted binary tree is full if every vertex has either two children or no children
// Number of triangulations of a convex polygon with n + 2 sides
// Number of non-isomorphic full binary trees with n interal nodes (having at least 1 child)
// Number of ways to connect the 2n points on a circle to form n disjoint chords
// C_0 = C_1 = 1
// C_n = Sum(k=0 to n-1) (C_k * C_{n-1-k}), n >= 2
// Analytical formula C_n = (1 / (n + 1)) * choose(2n, n)
int catalan[MAX];
void init() {
    catalan[0] = catalan[1] = 1;
    for (int i=2; i<=n; i++) {
        catalan[i] = 0;
        for (int j=0; j < i; j++) {
            catalan[i] += (catalan[j] * catalan[i-j-1]) % MOD;
            if (catalan[i] >= MOD) {
                catalan[i] -= MOD;
            }
        }
    }
}