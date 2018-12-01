int add(int a, int b)
{
    int c=a+b;
    if(c > mod)c-=mod;
    return c;
}
int mul(int a, int b)
{
    ll c=(ll)a*b;
    c%=mod;
    return (int)c;
}
struct matrix
{
    int N, M;
    vector<vector<int> >mat;
    matrix(int n, int m)
    {
        N=n, M=m;
        mat=vector<vector<int> >(N, vector<int>(M, 0));
    }
    matrix(vector<vector<int> >arr)
    {
        N=sz(arr), M=sz(arr[0]);
        mat=vector<vector<int> >(N, vector<int>(M, 0));
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++)
                mat[i][j]=arr[i][j];
    }
    matrix operator*(const matrix &o)
    {
        matrix ret(N, o.M);
        for(int i=0; i<ret.N; i++)
            for(int j=0; j<ret.M; j++)
                for(int k=0; k<M; k++)
                    ret.mat[i][j]=add(ret.mat[i][j], mul(mat[i][k], o.mat[k][j]));
        return ret;
    }
};
matrix pwr(matrix a, ll pw)
{
    matrix ret(a);
    while(pw > 0)
    {
        if(pw&1)ret=ret*a;
        a=a*a;
        pw>>=1;
    }
    return ret;
}