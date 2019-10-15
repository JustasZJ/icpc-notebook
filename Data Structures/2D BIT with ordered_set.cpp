#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
struct BIT
{
    ordered_set<int>f[maxn];
    void add(int i, int val)
    {
        for(; i <= maxn; i += i & -i)
            f[i].insert(val);
    }
    int get(int i, int lo, int hi)
    {
        int ret = 0;
        for(; i > 0; i -= i & -i)
            ret += f[i].order_of_key(hi + 1) - f[i].order_of_key(lo);
        return ret;
    }
    int get(int l, int r, int lo, int hi)
    {
        return get(r, lo, hi) - get(l - 1, lo, hi);
    }
};
