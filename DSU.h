template<typename T>
struct Dsu
{
private:
    vector<T> dsu_par, dsu_sz;
public:
    int m_n;

    Dsu(T n) 
    {
        m_n = n;
        dsu_par = vector<T>(n);
        dsu_sz = vector<T>(n, -1);
        for (int i = 0; i < n; i++)
            dsu_par[i] = i;
    }

    int getPar(int v) 
    {
        while ((v = dsu_par[v]) != dsu_par[v]);
        return v;
    }

    int getSize(int v) { return -dsu_sz[getPar(v)];}

    bool connected(int v, int u) { return getPar(v) == getPar(u); }

    void merge(int v, int u) 
    {
        v = getPar(v);
        u = getPar(u);
        if (v == u) return;
        if (dsu_sz[v] > dsu_sz[u]) swap(u, v);
        dsu_par[u] = v;
        dsu_sz[v] += dsu_sz[u];
    }
};