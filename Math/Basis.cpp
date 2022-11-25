/* Basis of vectors modulo 2 (for xor related problems) */
ll basis[62];
void add(ll a) {
    for (int bit = 61; bit >= 0; bit--) {
        if (a >> bit & 1) {
            if (basis[bit]) {
                a ^= basis[bit];
            } else {
                basis[bit] = a;
                return;
            }
        }
    }
}