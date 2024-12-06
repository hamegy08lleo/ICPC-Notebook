struct TSS {
        int nvar, nvrt;
        vector<vector<int>> adj;
        vector<bool> res;
        TSS(int nvar): nvar(nvar), nvrt(nvar * 2 + 2), adj(nvrt + 1), res(nvar + 1) {}

        int operator[](int i) { return res[i]; }
	// nu ? !u : u -> !nv ? !v : v
        void add(int u, bool nu, int v, bool nv) {
		u <<= 1; 
		v <<= 1; 
                u ^= nu; 
		v ^= nv; 
                adj[u].push_back(v);
        }
	int addvar() { 
		nvar++; 
		nvrt += 2; 
		adj.push_back({});
		adj.push_back({});  
		res.push_back({});
		return nvar; 
	}
	void atmostone(vector<int> & var) { 
		if (var.size() == 1) return; 
		int pre = addvar(); 
		add(var[0], 0, pre, 0); 
		add(var[0], 1, pre, 1); 
		add(pre, 0, var[0], 0); 
		add(pre, 1, var[0], 1); 
		for (int i = 1; i < var.size(); i++) { 
			add(var[i], 0, pre, 1); 
			add(pre, 0, var[i], 1); 
			int cur = addvar(); 
			add(var[i], 0, cur, 0); 
			add(pre, 0, cur, 0); 
			add(cur, 1, var[i], 1); 
			add(cur, 1, pre, 1); 
			pre = cur; 
		}
	}
        bool solve() {
                vector<int> in(nvrt + 1), low(nvrt + 1), id(nvrt + 1);
                stack<int> st;
                int curdfs = 0, curidx = 2 * nvrt + 1;
                auto tarjan = [&](auto&& f, int u) -> void {
                        in[u] = low[u] = ++curdfs;
                        st.push(u);
                        for (int v : adj[u]) {
                                if (!in[v]) {
                                        f(f, v);
                                        low[u] = min(low[u], low[v]);
                                } else if (!id[v]) {
                                        low[u] = min(low[u], in[v]);
                                }
                        }
                        if (low[u] == in[u]) {
                                int v;
                                do {
                                        v = st.top();
                                        st.pop();
                                        id[v] = curidx;
                                } while (v != u);
                                --curidx;
                        }
                };
                for (int i = 1; i <= nvrt; i++)
                        if (!in[i]) tarjan(tarjan, i);
                for (int i = 1; i <= nvar; i++) {
                        if (id[i] == id[i ^ 1]) return false;
                        res[i] = id[i] > id[i ^ 1];
                }
                return true;
        }
};
