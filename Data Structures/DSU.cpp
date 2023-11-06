struct DSU { 
        int n; 
        vector<int> par, sz; 

        DSU(int n): n(n) { 
                par = sz = vector<int> (n + 1); 
                fill(all(sz), 1LL); 
                iota(all(par), 0LL); 
        }
        int find(int v) { 
                while (v != par[v]) v = par[v] = par[par[v]]; 
                return v; 
        }

        bool join(int u, int v) { 
                u = find(u); 
                v = find(v); 
                if (u == v) return false; 
                if (sz[u] < sz[v]) swap(u, v); 
                sz[u] += sz[v]; 
                par[v] = u; 
                return true; 
        }

        int same(int u, int v) { 
                return find(u) == find(v); 
        }
};

