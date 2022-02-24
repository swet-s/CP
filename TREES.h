vector<int> ar[maxn];
bool vis[maxn];

namespace LCA
{
    const int maxl = 20;

    int LCA[maxn][maxl + 1];
    int lv[maxn];

    void dfs(int nd, int par, int lvl)
    {
        lv[nd] = lvl;
        LCA[nd][0] = par;

        for (auto& ch : ar[nd])
        {
            if (ch == par) continue;
            dfs(ch, nd, lvl + 1);
        }
    }

    int getLCA(int a, int b)
    {
        if (lv[b] < lv[a]) swap(a, b);

        int d = lv[b] - lv[a];

        while (d > 0)
        {
            int i = log2(d);
            b = LCA[b][i];
            d -= 1ll << i;
        }

        if (a == b) return a;
        for (int i = maxl; i >= 0; i--)
            if (LCA[a][i] != -1 && (LCA[a][i] != LCA[b][i]))
                a = LCA[a][i], b = LCA[b][i];

        return LCA[a][0];
    }

    void init(int n)
    {
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= maxl; j++)
                LCA[i][j] = -1;
            vis[i] = 0;
            ar[i].clear();
            lv[i] = 0;
        }

        int a, b;
        for (size_t i = 1; i < n; i++)
        {
            cin >> a >> b;
            ar[a].push_back(b);
            ar[b].push_back(a);
        }

        dfs(1, -1, 0);

        for (int i = 1; i <= maxl; i++)
        {
            for (int j = 1; j <= n; j++)
                if (LCA[j][i - 1] != -1)
                {
                    int par = LCA[j][i - 1];
                    LCA[j][i] = LCA[par][i - 1];
                }
        }
    }

    int dist(int a, int b)
    {
        return lv[a]+lv[b]-2*(lv[getLCA(a,b)]);
    }
}
using namespace LCA;