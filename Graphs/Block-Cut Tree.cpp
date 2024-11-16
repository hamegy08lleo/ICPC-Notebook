
/** @return the block-cut tree of a graph */
// 0-indexed, number of block can be up to 3 * n
vector<vector<int>> biconnected_components(vector<vector<int>> &g,
                                           vector<bool> &is_cutpoint, vector<int> &id) {
	int n = (int)g.size();
	vector<vector<int>> comps;
	vector<int> stk;
	vector<int> num(n);
	vector<int> low(n);

	is_cutpoint.resize(n);

	// Finds the biconnected components
	function<void(int, int, int &)> dfs = [&](int node, int parent, int &timer) {
		num[node] = low[node] = ++timer;
		stk.push_back(node);
		for (int son : g[node]) {
			if (son == parent) { continue; }
			if (num[son]) {
				low[node] = min(low[node], num[son]);
			} else {
				dfs(son, node, timer);
				low[node] = min(low[node], low[son]);
				if (low[son] >= num[node]) {
					is_cutpoint[node] = (num[node] > 1 || num[son] > 2);
					comps.push_back({node});
					while (comps.back().back() != son) {
						comps.back().push_back(stk.back());
						stk.pop_back();
					}
				}
			}
		}
	};

	int timer = 0;

	dfs(0, -1, timer);

	id.resize(n);

	// Build the block-cut tree
	function<vector<vector<int>>()> build_tree = [&]() {
		vector<vector<int>> t(1);
		int node_id = 0;
		for (int node = 0; node < n; node++) {
			if (is_cutpoint[node]) {
				id[node] = node_id++;
				t.push_back({});
			}
		}

		for (auto &comp : comps) {
			int node = node_id++;
			t.push_back({});
			for (int u : comp)
				if (!is_cutpoint[u]) {
					id[u] = node;
				} else {
					t[node].push_back(id[u]);
					t[id[u]].push_back(node);
				}
		}
		return t;

	};
	return build_tree();
}

