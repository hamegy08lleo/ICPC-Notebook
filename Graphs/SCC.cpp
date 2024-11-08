void tarjan(int u, int p) {
	in[u] = low[u] = ++curdfs;
	st.push(u);
	for (int v : adj[u]) {
		if (!in[v]) {
			tarjan(v, u); 
			low[u] = min(low[u], low[v]);
		} else if (!del[v]) {
			low[u] = min(low[u], in[v]);
		}
	}
	if (low[u] == in[u]) {
		int v;
		do {
			v = st.top();
			st.pop();
			scc[u].push_back(v); 
			top[v] = u; 
			del[v] = true; 
		} while (v != u);
	}
};


