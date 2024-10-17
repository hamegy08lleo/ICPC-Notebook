struct DSUTree { 
	vector<int> par, in, out, val, d; 
	vector<vector<int>> adj; 
	vector<vector<int>> up, mx;
	int num, n; 
	int cur = 0; 
	int find(int v) { 
		while (v != par[v]) v = par[v] = par[par[v]]; 
		return v; 
	}
	int newnode() { 
		num++; 
		par.push_back({}); 
		adj.push_back({}); 
		in.push_back({}); 
		out.push_back({}); 
		val.push_back({}); 
		d.push_back({}); 
		par[num] = num;
		return num; 
	}
	bool join(int u, int v, int i) { 
		u = find(u); 
		v = find(v); 
		if (u == v) return false; 
		int p = newnode();
		val[p] = i; 
		par[u] = par[v] = p;
		adj[p].push_back(u); 
		adj[p].push_back(v); 
		return true; 
	}
	void init(int n) { 
		num = this->n = n; 
		adj.resize(n + 1); 
		par.resize(n + 1); 
		in.resize(n + 1); 
		out.resize(n + 1); 
		val.resize(n + 1); 
		d.resize(n + 1); 
		iota(all(par), 0); 
	}
	void dfs(int u) { 
		in[u] = ++cur; 
		for (int v : adj[u]) { 
			d[v] = d[u] + 1; 
			up[v][0] = u; 
			mx[v][0] = max(val[v], val[u]); 
			dfs(v); 
		}
		out[u] = cur; 
	}
	void work() { 
		up = mx = vector<vector<int>>(num + 1, vector<int> (18)); 
		for (int i = 1; i <= num; i++) { 
			if (i == find(i)) {
				up[i][0] = i; 
				mx[i][0] = val[i]; 
				dfs(i); 
			}
		}
		for (int i = 1; i <= 18; i ++) { 
			for (int u = 1; u <= num; u++) { 
				up[u][i] = up[up[u][i-1]][i-1]; 
				mx[u][i] = max(mx[u][i-1], mx[up[u][i-1]][i-1]); 
			}
		}
	}
	pair<int, int> LCA(int u, int v) { 
		int ans = max(val[u], val[v]); 
		if (d[u] < d[v]) swap(u, v); 
		int det = d[u] - d[v]; 
		for (int i = 18; i >= 0; i--) { 
			if ((det >> i) & 1) { 
				ans = max(ans, mx[u][i]); 
				u = up[u][i]; 
			}
		}
		if (u == v) { 
			return {u, ans}; 
		}
		for (int i = 18; i >= 0; i--) { 
			if (up[u][i] != up[v][i]) { 
				ans = max({ans, mx[u][i], mx[v][i]}); 
				u = up[u][i]; 
				v = up[v][i]; 
			}
		}
		return {up[v][0], max({ans, up[u][0], up[v][0]})};
	}
};
