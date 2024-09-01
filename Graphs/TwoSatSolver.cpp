struct TSS { 
	int nvar; 
	int nvrt; 
	vector<vector<int>> adj;
	vector<int> res, scc, topo, vis, in, low, del, idx; 

	TSS(int nvar):
		nvar(nvar), 
		nvrt(nvar * 2), 
		adj(nvrt + 1), 
		res(nvar + 1), 
		scc(nvrt + 1), 
		in(nvrt + 1), 
		low(nvrt + 1), 
		del(nvrt + 1), 
		idx(nvrt + 1) {}


	int conj(int u) { 
		if (u > nvar) return u - nvar; 
		return u + nvar;
	}

	void add(int u, bool nu, int v, bool nv) { 
		if (nu) u = conj(u); 
		if (nv) v = conj(v); 
		adj[conj(u)].push_back(v); 
		adj[conj(v)].push_back(u); 
	}
	int curdfs = 0; 
	stack<int> st; 
	int curidx = nvrt; 
	void tarjan(int u) { 
		in[u] = low[u] = ++curdfs; 
		st.push(u); 
		for (int v : adj[u]) { 
			if (del[v]) continue; 
			if (!in[v]) { 
				tarjan(v); 
				low[u] = min(low[u], low[v]); 
			}
			else { 
				low[u] = min(low[u], in[v]); 
			}
		}
		if (low[u] == in[u]) { 
			idx[u] = curidx--; ; 
			while (st.top() != u) { 
				int v = st.top(); 
				st.pop(); 
				del[v] = true; 
				scc[v] = u; 
			}
			scc[u] = u; 
			del[u] = true; 
			st.pop(); 
		}
	}
	bool solve() { 
		for (int i = 1; i <= nvrt; i++) { 
			if (!in[i]) tarjan(i); 
		}
		for (int i = 1; i <= nvar; i++) { 
			if (scc[i] == scc[conj(i)]) return false; 
			res[i] = idx[scc[i]] > idx[scc[conj(i)]]; 
		}
		return true; 
	}
};

