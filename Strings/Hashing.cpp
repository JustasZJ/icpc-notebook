/* Works, but might be a little slow */
bool is_prime(int a) {
    if (a == 1) {
        return false;
    }
    if (a % 2 == 0) {
        return a == 2;
    }
    for (int i = 3; i * i <= a; i += 2) {
        if (a % i == 0) {
            return false;
        }
    }
    return true;
}

int pwr(int a, int pw, int MOD) {
    int ret = 1;
    while (pw > 0) {
        if (pw & 1) {
            ret = 1ll * ret * a % MOD;
        }
        a = 1ll * a * a % MOD;
        pw >>= 1;
    }
    return ret;
}
int modinv(int a, int MOD) {
    return pwr(a, MOD - 2, MOD);
}

struct hashing {
    vector<vector<int> >ha;
    vector<vector<int> >rha;
    static vector<vector<int> >pw;
    static vector<vector<int> >inv_pw;
    static vector<int>mods;
    static vector<int>BASE_INV;
    static int BASE;
    static int M;
    int N;
    
    static vector<int>zero_vector(int len) {
        vector<int>ret;
        for (int i = 0; i < len; i++) {
            ret.push_back(0);
        }
        return ret;
    }
    
    struct hash {
        vector<int>h;
        int len;
        
        hash() {
            h = zero_vector(M);
            len = 0;
        }
        
        hash(vector<int>h, int len) {
            this->h = h;
            this->len = len;
        }
        
        bool operator==(const hash& b) const {
            return h == b.h && len == b.len;
        }
        
        hash operator-(const hash& b) {
            hash c;
            c.h = h;
            
            for (int j = 0; j < M; j++) {
                c.h[j] -= b.h[j];
                if (c.h[j] < 0) {
                    c.h[j] += mods[j];
                }
                c.h[j] = 1ll * c.h[j] * inv_pw[b.len][j] % mods[j];
            }
            
            c.len = len - b.len;
            return c;
        }
        
        hash operator-=(const hash& b) {
            hash c = *this;
            c = c - b;
            this->h = c.h;
            this->len = c.len;
            return *this;
        }
        
        hash operator+(const hash& b) {
            hash c;
            c.h = h;
            
            for (int j = 0; j < M; j++) {
                c.h[j] += 1ll * pw[len][j] * b.h[j] % mods[j];
                if (c.h[j] >= mods[j]) {
                    c.h[j] -= mods[j];
                }
            }
            
            c.len = len + b.len;
            return c;
        }
        
        hash operator+=(const hash& b) {
            hash c = *this;
            c = c + b;
            this->h = c.h;
            this->len = c.len;
            return *this;
        }
        
        bool operator<(const hash& b) const {
            for (int i = 0; i < M; i++) {
                if (h[i] != b.h[i]) {
                    return h[i] < b.h[i];
                }
            }
            return len < b.len;
        }
    };
    
    hashing(string s) {
        if (M == 0 || BASE == 0) {
            cerr << "Initialize mods and base before creating a hashing instance!";
            exit(1);
        }
        init_string(s);
    }
    
    static void init_base() {
       mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<>distrib(3, (int)1e9);
        while (true) {
            BASE = distrib(rng);
            if (is_prime(BASE)) {
                break;
            }
        } 
    }
    
    static void init_mods(vector<int>new_mods) {
        mods = new_mods;
        M = (int)mods.size();
        BASE_INV = vector<int>(M);
        for (int j = 0; j < M; j++) {
            BASE_INV[j] = modinv(BASE, mods[j]);
        }
    }
    
    static void init_pows(int MAX_POW) {
        pw = vector<vector<int> >(MAX_POW + 1, vector<int>(M));
        inv_pw = vector<vector<int> >(MAX_POW + 1, vector<int>(M));

        for (int i = 0; i <= MAX_POW; i++) {
            for (int j = 0; j < M; j++) {
                if (i == 0) {
                    pw[i][j] = 1;
                    inv_pw[i][j] = 1;
                } else {
                    pw[i][j] = 1ll * pw[i - 1][j] * BASE % mods[j];
                    inv_pw[i][j] = 1ll * inv_pw[i - 1][j] * BASE_INV[j] % mods[j];
                }
            }
        }
    }

    void init_string(string s) {
        N = (int)s.size();
        
        ha = vector<vector<int> >(N, vector<int>(M));
        rha = vector<vector<int> >(N, vector<int>(M));
        
        init_pows(N * 2);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ha[i][j] = 1ll * pw[i][j] * (s[i] - 'a' + 1) % mods[j];
                rha[i][j] = 1ll * pw[i][j] * (s[N - i - 1] - 'a' + 1) % mods[j];
                    
                if (i > 0) {
                    ha[i][j] += ha[i - 1][j];
                    if (ha[i][j] >= mods[j]) {
                        ha[i][j] -= mods[j];
                    }
                    rha[i][j] += rha[i - 1][j];
                    if (rha[i][j] >= mods[j]) {
                        rha[i][j] -= mods[j];
                    }
                }
            }
        }
    }
    
    hash get_hash(int i, int j, bool reverse) {
        if (i > j) {
            return hash();
        }
        
        hash pref_i, pref_j;
        if (reverse) {
            i = N - i - 1;
            j = N - j - 1;
            swap(i, j);
            pref_i = (i == 0 ? hash() : hash(rha[i - 1], i));
            pref_j = hash(rha[j], j + 1);
        } else {
            pref_i = (i == 0 ? hash() : hash(ha[i - 1], i));
            pref_j = hash(ha[j], j + 1);
        }
        
        return pref_j - pref_i;
    }
};

vector<vector<int> > hashing::pw;
vector<vector<int> > hashing::inv_pw;
vector<int> hashing::mods;
vector<int> hashing::BASE_INV;
int hashing::BASE;
int hashing::M;