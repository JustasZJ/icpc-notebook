#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

struct RollingHash {
    static const ll mod0 = 1000000123, mod1 = 1000000007;
    static const ll base0 = 137, base1 = 163;
    
    vector<ll> po0, po1;
    vector<ll> hsh0, hsh1;
    
    void init(string str) {
        if (!po0.size()) po0 = po1 = {1};
        hsh0 = {base0}, hsh1 = {base1};
        
        for (int i = 0; i < (int)str.size(); i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 'a'-'A';
            hsh0.push_back((hsh0.back() * base0 % mod0 + str[i]) % mod0);
            hsh1.push_back((hsh1.back() * base1 % mod1 + str[i]) % mod1);
        }
    }
    
    pair<ll,ll> cut(int l, int r) {
        while (po0.size() <= r+1) {
            po0.push_back(po0.back() * base0 % mod0);
            po1.push_back(po1.back() * base1 % mod1);
        }
        
        return make_pair((hsh0[r+1]+mod0-(hsh0[l]*po0[r-l+1]%mod0))%mod0,
                         (hsh1[r+1]+mod1-(hsh1[l]*po1[r-l+1]%mod1))%mod1);
    }
} rh;
