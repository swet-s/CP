template<typename T>
struct SparseTable {
   int n, m;
   vector<vector<T>> st;
public:
   SparseTable(vector<T> a){
        n = a.size();
        m = log2(n) + 1;
        st = vector<vector<T>>(n, vector<T>(m));
        for (int i = 0; i < n; ++i) st[i][0] = a[i];
        for (int j = 1; j < m; ++j)
         for (int i = 0; i + (1 << j) <= n; ++i)
            st[i][j] = op(st[i][j-1], st[i+(1<<(j-1))][j-1]);
   }
   T op(T a, T b) { return min(a,b); }
   T query(int l, int r) {
        int j = log2(r-l+1);
        return op(st[l][j], st[r-(1<<j)+1][j]);
   }
};