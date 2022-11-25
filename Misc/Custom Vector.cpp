/* Description: Implementation of vector with negative indexing */
#include <bits/stdc++.h>
using namespace std;

template<class T>
struct MyVector {
    int offset;
    vector<T> vec_;

    MyVector(int n, int off, T &&values = T()) {
        vec_.resize(n, values);
        offset = off;
    }

    T& operator[](int i) {
        i += offset;
        assert(0 <= i && i < (int)vec_.size());
        return vec_[i];
    }
};

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    // Example usage
    MyVector<MyVector<int> > dp(10 + 1, 5, MyVector<int>(8 + 1, 4));

    for (int i = -5; i <= 5; i++) {
        for (int j = -4; j <= 4; j++) {
            dp[i][j] = i * j;
        }
    }

    for (int i = -5; i <= 5; i++) {
        for (int j = -4; j <= 4; j++) {
            cout << i << " " << j << " " << dp[i][j] << "\n";
        }
    }
    return 0;
}