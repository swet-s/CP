#pragma once

namespace STUFF
{
	// For Topological Sorting & Cycle Detection
	struct Kahns
	{
	    vi RES;

	    vector<vi> ar;
	    vi in;

	    Kahns(int n, int m)
	    {
	        ar = vector<vi>(n+1);
	        in = vi(n+1);

	        for (int i = 0; i < m; ++i)
	        {
	            int a,b;
	            cin>>a>>b;
	            ar[a].push_back(b);
	            in[b]++;
	        }
	    }
	        
	    bool run(int n)
	    {
	        queue<int> q;
	        for (size_t i = 1; i <= n; i++) if (in[i] == 0) q.push(i);

	        while (!q.empty())
	        {
	            int curr = q.front();
	            RES.push_back(curr);
	            q.pop();

	            for (auto& ch : ar[curr])
	            {
	                in[ch]--;
	                if (in[ch] == 0) q.push(ch);
	            }
	        }
	        return RES.size() == n;
	    }
	};

	//Strongly Connected Component && Condensation Graph
	struct StronglyConnectedComponent
	{
	    vector<vi> SCC;
	    vector<vi> CG;

	    vector<vi> ar,tr;
	    vi vis,order,comp,roots, rt_nd;

	    void dfs(int nd)
	    {
	        vis[nd] = 1;
	        for(auto& ch : ar[nd]) if(!vis[ch]) dfs(ch);
	        order.push_back(nd);
	    }
	 
	    void dfs1(int nd)
	    {
	        vis[nd] = 1;
	        for(auto& ch : tr[nd]) if(!vis[ch]) dfs1(ch);
	        comp.push_back(nd);
	    }

	    StronglyConnectedComponent(int n, int m)
	    {
	        ar = vector<vi>(n+1);
	        tr = vector<vi>(n+1);
	        CG = vector<vi>(n+1);
	        roots = vi(n+1);
	        vis = vi(n+1);

	        for (int i = 0; i < m; ++i)
	        {
	            int a,b;
	            cin>>a>>b;
	            ar[a].push_back(b);
	            tr[b].push_back(a);
	        }

	        for (int i = 1; i <= n; i++) if(!vis[i]) dfs(i);
	        for (int i = 1; i <= n; i++) vis[i] = 0;
	        reverse(all(order));
	        for (auto& v : order) if(!vis[v]) 
	        {
	            comp.clear();
	            dfs1(v);
	            int root = comp.front();
	            for (auto& e : comp) roots[e] = root; 
	            rt_nd.push_back(root);
	            SCC.push_back(comp);
	        }

	        for (int nd = 1; nd <= n; ++nd)
	            for (auto& ch : ar[nd])
	                if (roots[ch]!=roots[nd])
	                    CG[roots[nd]].push_back(roots[ch]);
	    }
	};
	

	//Dijkstra
	struct Dijkstra 
	{
	    const int inf = 4e18;
	    vi dists,par,vis,count;
	    vector<vector<pii>> ar;

	    Dijkstra(int n) 
	    {
	        dists = vi(n+1);
	        vis = vi(n+1);
	        par = vi(n+1);
	        count =  vi(n+1);
	        ar = vector<vector<pii>>(n+1);
	    }

	    void push_edge(int a, int b, int wt) 
	    {
	        ar[a].push_back({wt, b});
	        ar[b].push_back({wt, a});
	    }

	    void run(int src) 
	    {
	        fill(all(dists), inf);
	        fill(all(vis), 0);
	        fill(all(count), 0);
	        fill(all(par), -1);

	        priority_queue<pii, vector<pii>, greater<pii>> pq;
	        dists[src] = 0;
	        count[src]++;
	        pq.push({0, src});
	        while (!pq.empty()) 
	        {
	            pii foc = pq.top();
	            auto [w, f] = pq.top();
	            pq.pop();

	            if (vis[f]) continue;
	            vis[f] = 1;

	            dists[f] = min(dists[f], w);
	            for (pii x : ar[f]) 
	            {
	                int d = dists[f] + x.first;
	                if (d < dists[x.second]) 
	                {
	                    count[x.second]= 1;
	                    dists[x.second] = d;
	                    par[x.second] = f;
	                    pq.push({d, x.second});
	                }
	                else if (d == dists[x.second])
	                    count[x.second]++;
	            }
	        }
	    }
	};



	vi ar[maxn];
	bool is_Bipartite(int n)
	{
	    vi col(n, -1);

	    bool f = 1;
	    queue<int> q;
	    for (int i = 0; i < n; ++i) 
	    {
	        if (col[i] == -1) 
	        {
	            q.push(i);
	            col[i] = 0;
	            while (!q.empty()) 
	            {
	                int fr = q.front();
	                q.pop();
	                for (auto& ch : ar[fr])
	                {
	                    if (col[ch] == -1) 
	                    {
	                        col[ch] = col[fr] ^ 1;
	                        q.push(ch);
	                    } 
	                    else  f &= col[ch] != col[fr];
	                }
	            }
	        }
	    }
	    return f;
	}
	
}
using namespace STUFF;
