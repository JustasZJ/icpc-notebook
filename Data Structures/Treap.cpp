/*
* Source: https://github.com/bqi343/USACO/blob/master/Implementations/09%20-%20Range%20Queries%20(2)/15.3%20-%20BBST%20(4)/Treap.cpp
* Description: treap with max heap property
* Verification: http://www.spoj.com/problems/ORDERSET/
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
typedef pair<int, int>pii;
const int maxn=1e5+100;
struct node
{
    int val, pri, sz;
    node *l, *r;

    node (int v)
    {
        val = v, sz = 1, pri = rand()+(rand()<<15);
        l = r = NULL;
    }

    void recalc()
    {
        sz = 1+(l?l->sz:0)+(r?r->sz:0);
    }
};
typedef node* pnode;
pair<pnode,pnode> split(pnode t, int v)/// >= v goes to the right
{
    if (!t) return {t,t};

    if (v <= t->val)
    {
        auto p = split(t->l, v);
        t->l = p.second;
        t->recalc();
        return {p.first, t};
    }
    else
    {
        auto p = split(t->r, v);
        t->r = p.first;
        t->recalc();
        return {t, p.second};
    }
}

pair<pnode,pnode> split_by_order(pnode t, int v)
{
    if (!t) return {t,t};
    int tmp = t->l?t->l->sz:0;
    if (v <= tmp)
    {
        auto p = split_by_order(t->l, v);
        t->l = p.second;
        t->recalc();
        return {p.first, t};
    }
    else
    {
        auto p = split_by_order(t->r, v-tmp-1);
        t->r = p.first;
        t->recalc();
        return {t, p.second};
    }
}

pnode merge(pnode left, pnode right)
{
    if (!left) return right;
    if (!right) return left;

    if (left->pri > right->pri)
    {
        left->r = merge(left->r,right);
        left->recalc();
        return left;
    }
    else
    {
        right->l = merge(left,right->l);
        right->recalc();
        return right;
    }
}

pnode ins(pnode x, int v)
{
    auto a = split(x,v);
    auto b = split(a.second,v+1);
    return merge(a.first,merge(new node(v),b.second));
}

pnode del(pnode x, int v)
{
    auto a = split(x,v), b = split(a.second,v+1);
    return merge(a.first,b.second);
}

pnode root;

int order_of_key(int x)
{
    auto a = split(root,x);
    int t = a.first?a.first->sz:0;
    root = merge(a.first,a.second);
    return t;
}

int find_by_order(int x)
{
    auto a = split_by_order(root,x);
    auto b = split_by_order(a.first,x-1);
    int t = b.second->val;
    root = merge(merge(b.first,b.second),a.second);
    return t;
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0);
    int Q;
    cin >> Q;
    for(int i=0; i<Q; i++)
    {
        char c;
        int d;
        cin >> c >> d;
        if (c == 'I') root = ins(root,d);
        else if (c == 'D') root = del(root,d);
        else if (c == 'K')
        {
            if (!root || root->sz < d) cout << "invalid\n";
            else cout << find_by_order(d) << "\n";
        }
        else cout << order_of_key(d) << "\n";
    }
}
