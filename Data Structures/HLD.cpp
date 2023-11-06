struct HLD { 
        int n; 
        int root; 
        vector<int> sz, par, dep, top, in, out, seq; 
        vector<vector<int>> adj; 
        int curdfs = 0; 
        HLD(int n): n(n) { 
                par = sz = dep = top = in = out = seq = vector<int> (n + 1); 
                adj.resize(n + 1); 
        }

        void edge(int u, int v) { 
                adj[u].push_back(v); 
                adj[v].push_back(u);
        }

        void start(int root = 1) {
                this->root = root; 
                par[root] = root; 
                top[root] = root; 
                dfssz(root); 
                dfshld(root); 
        }

        void dfssz(int u) { 
                if (u != root) { 
                        adj[u].erase(find(all(adj[u]), par[u])); 
                }
                sz[u] = 1; 
                for (int &v : adj[u]) { 
                        dep[v] = dep[u] + 1; 
                        par[v] = u; 
                        dfssz(v); 
                        sz[u] += sz[v]; 
                        if (sz[v] > sz[adj[u][0]]) {
                                swap(adj[u][0], v); 
                        }
                }
        }

        void dfshld(int u) { 
                in[u] = ++curdfs; 
                seq[in[u]] = u; 
                for (int v : adj[u]) { 
                        top[v] = (v == adj[u][0] ? top[u] : v); 
                        dfshld(v); 
                }
                out[u] = curdfs; 
        }

        int lca(int u, int v) { 
                while (top[u] != top[v]) { 
                        if (dep[top[u]] > dep[top[v]]) {
                                u = par[top[u]]; 
                        }
                        else { 
                                v = par[top[v]]; 
                        }
                }
                return (dep[u] < dep[v] ? u : v); 
        }

        bool isancestor(int u, int v) { 
                return in[u] <= in[v] && out[v] <= out[u]; 
        }
};
